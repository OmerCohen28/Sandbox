using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Net;

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

        [DllImport("Ws2_32.dll", SetLastError = true)]
        public static extern IntPtr socket(
    int af,
    int type,
    int protocol);

        
        public const int AF_INET = 2;
        public const int SOCK_STREAM = 1;
        public const int IPPROTO_TCP = 6;

       
        [DllImport("Ws2_32.dll", SetLastError = true)]
       public static extern int connect(
            IntPtr socket,
            byte[] socketAddress,
            int socketAddressSize);

        [DllImport("advapi32.dll", CharSet = CharSet.Ansi, SetLastError = true)]
        public static extern int RegCreateKeyExA(
UIntPtr hKey,
string lpSubKey,
int Reserved,
string lpClass,
int dwOptions,
int samDesired,
IntPtr lpSecurityAttributes,
out UIntPtr phkResult,
out int lpdwDisposition);

        // Constants for the RegCreateKeyExA function
        public const int REG_OPTION_NON_VOLATILE = 0;
        public const int REG_CREATED_NEW_KEY = 1;

        public static UIntPtr HKEY_LOCAL_MACHINE = new UIntPtr(0x80000002u);
        public static UIntPtr HKEY_CURRENT_USER = new UIntPtr(0x80000001u);

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
            uint length = (uint)buffer.Length * sizeof(char) / 2;
            Console.WriteLine(length);
            uint bytesWritten;
            NativeOverlapped tmpOverlapped = new NativeOverlapped();
            Console.WriteLine("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

            WinAPI.WriteFile
                (
                    hFile, new StringBuilder(buffer), length, out bytesWritten, ref tmpOverlapped

                );

            Console.WriteLine("************************************");


            // Open the HKEY_CURRENT_USER root key
            UIntPtr keyHandle;
            int disposition;
            int result = WinAPI.RegCreateKeyExA(
                WinAPI.HKEY_CURRENT_USER,
                "A_Virus_Key",
                0,
                null,
                WinAPI.REG_OPTION_NON_VOLATILE,
                0,
                IntPtr.Zero,
                out keyHandle,
                out disposition);

            //int port = 80;
            //while (port < 83)
            //{

            //    Console.WriteLine($"Trying to connect to host through port {port}");
            //    // Parse the target host and port from the command line arguments
            //    string host = "142.250.186.68";

            //    // Resolve the target host to an IP address
            //    IPHostEntry hostEntry = Dns.GetHostEntry(host);
            //    IPAddress[] addresses = hostEntry.AddressList;

            //    // Create a socket for connecting to the target host
            //    IntPtr socketHandle = WinAPI.socket(WinAPI.AF_INET, WinAPI.SOCK_STREAM, WinAPI.IPPROTO_TCP);
            //    if (socketHandle == IntPtr.Zero)
            //    {
            //        continue;
            //    }

            //    // Create a socket address for the target host and port
            //    EndPoint endPoint = new IPEndPoint(addresses[0], port);
            //    int endPointSize = endPoint.Serialize();
            //    byte[] socketAddress = new byte[endPointSize];
            //    Buffer.BlockCopy(endPoint.Serialize(), 0, socketAddress, 0, endPointSize);

            //    // Try to connect to the target host and port
            //    int result = WinAPI.connect(socketHandle, socketAddress, endPointSize);
            //    if (result != 0)
            //    {
            //        continue;
            //    }
            //    Console.WriteLine($"Successfully connected to host through port {port}");
            //}


        }
    }
}
