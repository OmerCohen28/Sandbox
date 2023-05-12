using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Python.Runtime;
using IronPython;
using IronPython.Compiler;
using Python;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;
using System.IO;

namespace Graphics
{
    public partial class Form2 : Form
    {
        static Dictionary<string, Color> function_to_color = new Dictionary<string, Color>();
        public static TcpClient client = new TcpClient();
        public Form2()
        {
            InitializeComponent();
        }
        public static void init_sock()
        {
            try
            {

                client.Connect("127.0.0.1", 50505);

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            // Check if the connection is successful
            if (client.Connected)
            {
                MessageBox.Show("Connected to the server.");

            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (this.radioButton1.Checked)
            {
                this.radioButton1.Text = "X";
            }
            else
            {
                this.radioButton1.Text= string.Empty;
            }
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            if (this.radioButton2.Checked)
            {
                this.radioButton2.Text = "X";
            }
            else
            {
                this.radioButton2.Text = string.Empty;
            }
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            NetworkStream stream = client.GetStream();
            if (this.radioButton1.Checked)
            {
                try
                {
                    function_to_color.Add(this.textBox1.Text, Color.Orange);
                    byte[] data = Encoding.UTF8.GetBytes("w"+this.textBox1.Text);
                    stream.Write(data, 0, data.Length);
                    byte[] buffer = new byte[1024];
                    int bytesRead = stream.Read(buffer, 0, buffer.Length);
                    string response = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                    if(response == "0")
                    {
                        MessageBox.Show("Invalid function");
                        return;
                    }
                }
                catch
                {
                    MessageBox.Show("You Have Entered a Function Twice");
                    return;
                }
            }
            else if(this.radioButton2.Checked)
            {
                try
                {
                    function_to_color.Add(this.textBox1.Text, Color.DarkRed);
                    byte[] data = Encoding.UTF8.GetBytes("b"+this.textBox1.Text);
                    stream.Write(data, 0, data.Length);
                    byte[] buffer = new byte[1024];
                    int bytesRead = stream.Read(buffer, 0, buffer.Length);
                    string response = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                    if (response == "0")
                    {
                        MessageBox.Show("Invalid function");
                        return;
                    }
                }
                catch
                {
                    MessageBox.Show("You Have Entered a Function Twice");
                    return;
                }
            }
            else
            {
                MessageBox.Show("You Must Select Either Warn/Block");
                return;
            }

            this.listBox1.Items.Add(this.textBox1.Text);
            this.radioButton1.Checked = false;
            this.radioButton2.Checked = false;


        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.listBox1.Items.Clear();
        }


        private void listBox1_DoubleClick(object sender, EventArgs e)
        {
            if (this.listBox1.SelectedItem != null)
            {
                string? selectedItem = this.listBox1.SelectedItem.ToString();
                if (selectedItem != null)
                {
                    this.listBox1.Items.Remove(selectedItem);
                }
            }
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            this.label5.ForeColor = this.radioButton3.BackColor;
        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            this.label5.ForeColor = this.radioButton4.BackColor;
        }

        private void radioButton5_CheckedChanged(object sender, EventArgs e)
        {
            this.label5.ForeColor = this.radioButton5.BackColor;
        }

        private void radioButton6_CheckedChanged(object sender, EventArgs e)
        {
            this.label6.ForeColor = this.radioButton6.BackColor;
        }

        private void radioButton7_CheckedChanged(object sender, EventArgs e)
        {
            this.label6.ForeColor = this.radioButton7.BackColor;
        }

        private void radioButton8_CheckedChanged(object sender, EventArgs e)
        {
            this.label6.ForeColor = this.radioButton8.BackColor;
        }

        private void radioButton10_CheckedChanged(object sender, EventArgs e)
        {
            this.label7.ForeColor = this.radioButton10.BackColor;
        }

        private void radioButton9_CheckedChanged(object sender, EventArgs e)
        {
            this.label7.ForeColor = this.radioButton9.BackColor;
        }

        private void radioButton11_CheckedChanged(object sender, EventArgs e)
        {
            this.label7.ForeColor = this.radioButton11.BackColor;
        }

        private void radioButton18_CheckedChanged(object sender, EventArgs e)
        {
            this.label11.ForeColor = this.radioButton18.BackColor;
        }

        private void radioButton19_CheckedChanged(object sender, EventArgs e)
        {
            this.label11.ForeColor = this.radioButton19.BackColor;
        }

        private void radioButton20_CheckedChanged(object sender, EventArgs e)
        {
            this.label11.ForeColor = this.radioButton20.BackColor;
        }

        private void radioButton15_CheckedChanged(object sender, EventArgs e)
        {
            this.label10.ForeColor = this.radioButton15.BackColor;
        }

        private void radioButton16_CheckedChanged(object sender, EventArgs e)
        {
            this.label10.ForeColor = this.radioButton16.BackColor;
        }

        private void radioButton17_CheckedChanged(object sender, EventArgs e)
        {
            this.label10.ForeColor = this.radioButton17.BackColor;
        }

        private void radioButton12_CheckedChanged(object sender, EventArgs e)
        {
            this.label9.ForeColor = this.radioButton12.BackColor;
        }

        private void radioButton14_CheckedChanged(object sender, EventArgs e)
        {
            this.label9.ForeColor = this.radioButton14.BackColor;
        }

        private void radioButton13_CheckedChanged(object sender, EventArgs e)
        {
            this.label9.ForeColor = this.radioButton13.BackColor;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            NetworkStream stream = client.GetStream();
            byte[] data = Encoding.UTF8.GetBytes("stop");
            stream.Write(data, 0, data.Length);

            Process process2 = new Process();
            process2.StartInfo.FileName = "\"D:\\Actual sandbox sln\\injectDll\\Debug\\injectDll.exe\"";
            process2.StartInfo.Arguments = $"\"D:\\Actual sandbox sln\\virus\\Debug\\virus.exe\" \"{trackBar1.Value}\"";
            process2.Start();
            InitializeComponent();
            Program.form2.Hide();
            Program.form3.ShowDialog();
            Thread thread = new Thread(Program.form3.updateGUIData);
            thread.Start();
            this.Dispose();
        }

        private void label13_Click(object sender, EventArgs e)
        {

        }

        private void label16_Click(object sender, EventArgs e)
        {

        }

        private void trackBar1_ValueChanged(object sender, EventArgs e)
        {
            label16.Text = $"RAM allowed: {trackBar1.Value} MB";
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void listBox1_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {

        }
    }
}
