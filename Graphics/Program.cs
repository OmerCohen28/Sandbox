namespace Graphics
{
    internal static class Program
    {
        public static Form1 form = new Form1();
        public static Form2 form2 = new Form2();
        public static Form3 form3 = new Form3();

        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.Run(form);
        }
    }
}