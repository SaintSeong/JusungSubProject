using Microsoft.Win32;
using System;
using System.Diagnostics;
using System.Management;
using System.Runtime.InteropServices;
using System.Text;

namespace MyApp // Note: actual namespace depends on the project name.
{
    internal class Program
    {

        private static void QshareFolder(string FolderPath, string ShareName, string Description)
        {
            try
            {
                // Create a ManagementClass object

                ManagementClass managementClass = new ManagementClass("Win32_Share");

                // Create ManagementBaseObjects for in and out parameters

                ManagementBaseObject inParams = managementClass.GetMethodParameters("Create");

                ManagementBaseObject outParams;

                // Set the input parameters

                inParams["Description"] = Description;

                inParams["Name"] = ShareName;

                inParams["Path"] = FolderPath;

                inParams["Type"] = 0x0; // Disk Drive

                //Another Type:

                // DISK_DRIVE = 0x0

                // PRINT_QUEUE = 0x1

                // DEVICE = 0x2

                // IPC = 0x3

                // DISK_DRIVE_ADMIN = 0x80000000

                // PRINT_QUEUE_ADMIN = 0x80000001

                // DEVICE_ADMIN = 0x80000002

                // IPC_ADMIN = 0x8000003

                //inParams["MaximumAllowed"] = int maxConnectionsNum;

                // Invoke the method on the ManagementClass object

                outParams = managementClass.InvokeMethod("Create", inParams, null);

                // Check to see if the method invocation was successful

                if ((uint)(outParams.Properties["ReturnValue"].Value) != 0)

                {

                    throw new Exception("Unable to share directory.");

                }

            }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.Message, "error!");
            }
        }

        private static void Func()
        {
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(i + 1);
                Thread.Sleep(100);
            }
        }

        private static void Func(object obj)
        {
            int num = (int)obj;
            for (int i = 0; i < num; i++)
            {
                Console.WriteLine(i + 1);
                Thread.Sleep(100);
            }
        }
        // 외부에서 Kernel32를 불러온 것
        // DllImport 기능
        [DllImport("kernel32")]
        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);
        
        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section, string key, string def, StringBuilder retVal, int size, string filePath);
        
        [DllImport("kernel32")]
        private static extern int GetPrivateProfileInt(string section, string key, int def, string filePath);
        static void Main(string[] args)
        {
            // Registry 속성 자체에 Root가 설정
            // using Microsoft.Win32;
            RegistryKey reg = Registry.LocalMachine;
            //Registry.LocalMachine.SetValue();
            //Registry.LocalMachine.GetValue();
            //Registry.LocalMachine.DeleteSubKey();
            reg = reg.OpenSubKey("Software\\GeoService\\GeoService-Xr", true);
            Object val = reg.GetValue("INSTALL_PATH");
            reg.DeleteSubKey("");
            reg.SetValue("","");

            // Process 찾기
            Process[] processes = Process.GetProcessesByName("notepad");
            foreach (Process p in processes)
            {
                Console.WriteLine($"Notepad process found with ID: {p.Id}");
                p.Kill();
            }

            // Thread 설정하기
            Thread myThread = new Thread(Func);
            myThread.IsBackground = true; // Thread BackGround 설정
            myThread.Start();
            myThread.Abort(); // Thread 강제 종료

            // 터미널 설정
            var folderName = "test";
            string targetDir = "D:\\test";
            var process = new Process();
            process.StartInfo = new ProcessStartInfo()
            {
                UseShellExecute = false,
                RedirectStandardError = true,
                RedirectStandardInput = true,
                RedirectStandardOutput = true,
                CreateNoWindow = true,
                ErrorDialog = false,
                WindowStyle = ProcessWindowStyle.Hidden,
                FileName = @"C:\Users\pand3\Desktop\cmd.exe",
                //Arguments = $"/C net share \"{folderName}\" /delete"
                Arguments = $"/C net share {folderName}=\"{targetDir}\" /Grant:Everyone,READ"
            };
            process.Start();
            Console.WriteLine(process.StandardOutput.ReadToEnd());
            process.WaitForExit();
            //QshareFolder("D:\\test", "Test Share", "This is a Test Share");
            //ManagementObject share = new ManagementObject("Win32_Share.Name=\"test\"");
            //share.Delete();
        }
    }
}