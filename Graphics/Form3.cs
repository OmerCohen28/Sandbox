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
            WinApiHooksData[] dataArray = GetData.GetDLLData();
            if (dataArray.Length == 0) { return; }
            foreach (WinApiHooksData data in dataArray)
            {
                //MessageBox.Show(data.ToString());
                FlowLayoutPanel p = new FlowLayoutPanel();
                p.Dock = DockStyle.Top;
                p.FlowDirection = FlowDirection.TopDown;
                p.WrapContents = false;
                p.AutoScroll = true;
                p.AutoSize = true;
                p.AutoSizeMode = AutoSizeMode.GrowAndShrink;
                Label name = new Label();
                name.Font = new System.Drawing.Font("Segoe Print", 16F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point);
                name.ForeColor = System.Drawing.Color.LightGreen;
                name.Text = data.funcName;
                name.AutoSize = true;

                p.Controls.Add(name);

                for (int i = 0; i < data.parameters.Length; i++)
                {
                    Label param = new Label();
                    param.Font = new System.Drawing.Font("Segoe Print", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
                    param.ForeColor = System.Drawing.Color.LightGreen;
                    param.Text = data.parameters[i];
                    param.AutoSize = true;

                    p.Controls.Add(param);


                }
                Label time = new Label();
                time.Font = new System.Drawing.Font("Segoe Print", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
                time.ForeColor = System.Drawing.Color.LightGreen;
                time.Text = data.timeCalled;
                time.AutoSize = true;

                p.Controls.Add(time);

                Label space = new Label();
                space.Height = 20;
                p.Controls.Add(space);


                panel1.Controls.Add(p);
            }

            panel1.AutoScroll = true;



        }
    }
}
