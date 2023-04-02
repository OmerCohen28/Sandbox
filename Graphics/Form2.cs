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
    public partial class Form2 : Form
    {
        static Dictionary<string, Color> function_to_color = new Dictionary<string, Color>();
        public Form2()
        {
            InitializeComponent();
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
            if (this.radioButton1.Checked)
            {
                try
                {
                    function_to_color.Add(this.textBox1.Text, Color.Orange);
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
    }
}
