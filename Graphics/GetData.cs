using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Mono.Unix.Native;
using static Community.CsharpSqlite.Sqlite3;

namespace Graphics
{
    internal class GetData
    {
        void x()
        {

        }
    }

    class WinApiHooksData
    {
        static private long filePosition = 0;
        private string funcName { get; set; }
        private string timeCalled { get; set; }
        private string[] parameters { get; set; }
        
        void GetDataFromFile(string filename)
        {
            using (StreamReader reader = new StreamReader(filename))
            {
                string content = reader.ReadToEnd();

                Console.WriteLine(content);
            }
        }
        WinApiHooksData()
        {
            string content;
            using (FileStream fileStream = new FileStream("C:\\Users\\Omer Cohen\\Documents\\Programming\\Sandbox\\functions_sockets.txt", FileMode.Open, FileAccess.Read))
            {
                fileStream.Seek(filePosition, SeekOrigin.Begin);

                using (StreamReader reader = new StreamReader(fileStream))
                {
                    content = reader.ReadToEnd();

                    //Console.WriteLine(content);

                    filePosition = fileStream.Position;
                }
            }
            funcName = content.Split("$")[0];
            timeCalled = System.DateTime.Now.ToString();
            parameters = new string[content.Split("$").Length - 1];
            for (int i = 1; i < content.Split("$").Length; i++)
            {
                parameters[i - 1] = content.Split("$")[i];
            }
        }

    }

}
