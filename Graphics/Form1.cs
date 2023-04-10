using System.Drawing;

namespace Graphics
{
    public partial class Form1 : Form
    {
        string fileToExamine = "";
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(fileToExamine == "")
            {
                MessageBox.Show("You must drag a file to examine before proceeding!");
                return;
            }
            Program.form.Hide();
            Program.form2.ShowDialog();
            this.Dispose();
        }

        private void panel1_DragDrop(object sender, DragEventArgs e)
        {
            if (e.Data == null)
            {
                return;
            }

            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);

            if (files.Length > 1)
            {
                MessageBox.Show("Only one file per run is allowed");
                return;
            }

            string extension = Path.GetExtension(files[0]);

            if(extension != ".exe" && extension != ".py")
            {
                MessageBox.Show("Only python files and .exe x86 files are currently supported");
                return;
            }

            fileToExamine = files[0];

            this.button2.Text = "File Selected: " + Path.GetFileName(fileToExamine);
        }

        private void panel1_DragEnter(object sender, DragEventArgs e)
        {
            if(e.Data == null)
            {
                return;
            }
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effect = DragDropEffects.Copy;
            }
        }

        private void panel1_DragOver(object sender, DragEventArgs e)
        {

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

        }
    }
}