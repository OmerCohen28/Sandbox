#include <map>
#include <string>
#include <Windows.h>

/*
- after creating a new tmp file, need to copy the contents from the original file
- test a lot
*/

class Divertor {
	std::map<std::string, std::string>* file_names;
	std::map<std::string, HANDLE>* file_to_handle;
	int tmp_counter;

public:
	Divertor() : file_names{ new std::map<std::string, std::string> },
		file_to_handle{ new std::map<std::string, HANDLE> },
		tmp_counter{ 0 } {}

	HANDLE create(LPCSTR path) {
		if (file_names->find(std::to_string((char)*path)) == file_names->end()) {
			//not found
			char buf[6];
			snprintf(buf, 6, "tmp%d", tmp_counter);
			++tmp_counter;
			file_names->insert({ path,buf });
			HANDLE file = CreateFileA(
				buf,
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);
			file_to_handle->insert({ path,file });
			return file;
		}
		else {
			//found
			for (auto it = file_to_handle->begin();it != file_to_handle->end();++it) {
				if (it->first == path) {
					if (it->second == INVALID_HANDLE_VALUE) {
						return CreateFileA(
							path,
							GENERIC_READ | GENERIC_WRITE,
							0,
							NULL,
							OPEN_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL
						);
					}
					else {
						return it->second;
					}
				}
			}

		}
	}

	

};