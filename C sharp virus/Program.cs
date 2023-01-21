using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

namespace C_sharp_virus
{
    public class WinAPI
    {
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern IntPtr CreateFile(
     [MarshalAs(UnmanagedType.LPTStr)] string filename,
     [MarshalAs(UnmanagedType.U4)] FileAccess access,
     [MarshalAs(UnmanagedType.U4)] FileShare share,
     IntPtr securityAttributes, // optional SECURITY_ATTRIBUTES struct or IntPtr.Zero
     [MarshalAs(UnmanagedType.U4)] FileMode creationDisposition,
     [MarshalAs(UnmanagedType.U4)] FileAttributes flagsAndAttributes,
     IntPtr templateFile);

        [DllImport("kernel32.dll", CharSet = CharSet.Ansi, SetLastError = true)]
        public static extern IntPtr CreateFileA(
             [MarshalAs(UnmanagedType.LPStr)] string filename,
             [MarshalAs(UnmanagedType.U4)] FileAccess access,
             [MarshalAs(UnmanagedType.U4)] FileShare share,
             IntPtr securityAttributes,
             [MarshalAs(UnmanagedType.U4)] FileMode creationDisposition,
             [MarshalAs(UnmanagedType.U4)] FileAttributes flagsAndAttributes,
             IntPtr templateFile);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        public static extern IntPtr CreateFileW(
             [MarshalAs(UnmanagedType.LPWStr)] string filename,
             [MarshalAs(UnmanagedType.U4)] FileAccess access,
             [MarshalAs(UnmanagedType.U4)] FileShare share,
             IntPtr securityAttributes,
             [MarshalAs(UnmanagedType.U4)] FileMode creationDisposition,
             [MarshalAs(UnmanagedType.U4)] FileAttributes flagsAndAttributes,
             IntPtr templateFile);

        [DllImport("kernel32.dll", BestFitMapping = true, CharSet = CharSet.Ansi)]
        public static extern bool WriteFile(IntPtr hFile, System.Text.StringBuilder lpBuffer,
     uint nNumberOfBytesToWrite, out uint lpNumberOfBytesWritten,
     [In] ref System.Threading.NativeOverlapped lpOverlapped);
    }


    internal class Program
    {
        static void Main(string[] args)
        {
            Thread.Sleep(3000);
            string path = @"..\test.txt";
            //Console.WriteLine("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
            IntPtr hFile = WinAPI.CreateFileA(
                path,
                FileAccess.ReadWrite,
                FileShare.None,
                IntPtr.Zero,
                FileMode.OpenOrCreate,
                FileAttributes.Normal,
                IntPtr.Zero
                );
            Console.WriteLine("574975847583475847857348578934");
            string buffer = "Hello World!\n";
            uint length = (uint)buffer.Length * sizeof(char)/2;
            Console.WriteLine(length);
            uint bytesWritten;
            NativeOverlapped tmpOverlapped = new NativeOverlapped();
            Console.WriteLine("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

            WinAPI.WriteFile
                (
                    hFile, new StringBuilder(buffer), length, out bytesWritten, ref tmpOverlapped

                );

            Console.WriteLine("************************************");

        }
    }
}
