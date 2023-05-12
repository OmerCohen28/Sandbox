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

        public static WinApiHooksData[] GetDLLData()
        {
            string content;
            using (FileStream fileStream = new FileStream("D:\\Actual sandbox sln\\log.txt", FileMode.Open, FileAccess.Read))
            {
                fileStream.Seek(WinApiHooksData.filePosition, SeekOrigin.Begin);

                using (StreamReader reader = new StreamReader(fileStream))
                {
                    content = reader.ReadToEnd();

                    //Console.WriteLine(content);

                    WinApiHooksData.filePosition = fileStream.Position;
                }
            }
            string[] data = content.Split("%");
            WinApiHooksData[] result = new WinApiHooksData[data.Length - 1];
            int index = 0;
            foreach (string d in data)
            {
                if (index == data.Length - 1) { return result; }
                string funcName = d.Split("$")[0];
                string timeCalled = System.DateTime.Now.ToString();
                string[] parameters = new string[d.Split("$").Length - 1];
                for (int i = 1; i < d.Split("$").Length; i++)
                {
                    parameters[i - 1] = d.Split("$")[i];
                }
                result[index] = new WinApiHooksData(funcName, timeCalled, parameters);
                index++;
            }
            return result;

        }
    }

    class WinApiHooksData
    {
        static public long filePosition = 0;
        public string funcName { get; set; }
        public string timeCalled { get; set; }
        public string[] parameters { get; set; }

        void GetDataFromFile(string filename)
        {
            using (StreamReader reader = new StreamReader(filename))
            {
                string content = reader.ReadToEnd();

                Console.WriteLine(content);
            }
        }
        public WinApiHooksData(string func_name, string timeCalled, string[] param)
        {
            this.funcName = func_name;
            this.timeCalled = timeCalled;
            this.parameters = new string[param.Length];
            for (int i = 0; i < param.Length; i++)
            {
                this.parameters[i] = param[i];
            }

        }

        public override string ToString()
        {
            return $"func: {funcName}, param_length: {parameters.Length}";
        }

    }

}