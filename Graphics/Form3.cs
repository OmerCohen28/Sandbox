using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Graphics
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }

        public void updateGUIData()
        {
            if (Program.IsVirusFinished)
            {
                button3.Enabled = true;
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {
            FlowLayoutPanel p = new FlowLayoutPanel();
            p.Dock = DockStyle.Top;
            p.FlowDirection = FlowDirection.TopDown;
            p.WrapContents= false;
            p.AutoScroll= true;
            p.AutoSize = true;
            p.AutoSizeMode= AutoSizeMode.GrowAndShrink;

            string s = "WriteFile$hFile: Can't Parse Data$lpBuffer: nami swannn\r\n$nNumberOfBytesToWrite: 12$lpNumberOfBytesWritten: NULL$lpOverlapped: NULL$dsajhkdjsadas$";
            string[] data = s.Split("$");

            Label name = new Label();
            name.Font = new System.Drawing.Font("Segoe Print", 16F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point);
            name.ForeColor = System.Drawing.Color.LightGreen;
            name.Text = data[0];
            name.AutoSize = true;

            p.Controls.Add(name);

            for (int i = 1; i < data.Length - 1; i++)
            {
                Label param = new Label();
                param.Font = new System.Drawing.Font("Segoe Print", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
                param.ForeColor = System.Drawing.Color.LightGreen;
                param.Text = data[i];
                param.AutoSize = true;

                p.Controls.Add(param);


            }

            Label space = new Label();
            space.Height = 20;
            p.Controls.Add(space);


            panel1.Controls.Add(p);
            panel1.AutoScroll = true;



        }
    }
}
