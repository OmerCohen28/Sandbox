using System.Windows.Forms;

namespace Graphics
{
    partial class Form2
    {
        private void MyListBox_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            // Set the height of each item to 25 pixels.
            e.ItemHeight = 25;
        }

        private void ListBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            e.DrawBackground();

            ListBox listBox = (ListBox)sender;

            // Get the current item's text.
            string itemText = listBox.GetItemText(listBox.Items[e.Index]);

            // Look up the color for the current item's text in the dictionary.
            Color itemColor = function_to_color[itemText];

            // Draw the current item's text with the desired color.
            e.Graphics.DrawString(itemText, e.Font, new SolidBrush(itemColor), e.Bounds, StringFormat.GenericDefault);

            // Draw the focus rectangle if the item has focus.
            e.DrawFocusRectangle();
        }

        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.button1 = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.button2 = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.radioButton4 = new System.Windows.Forms.RadioButton();
            this.radioButton5 = new System.Windows.Forms.RadioButton();
            this.radioButton6 = new System.Windows.Forms.RadioButton();
            this.radioButton7 = new System.Windows.Forms.RadioButton();
            this.radioButton8 = new System.Windows.Forms.RadioButton();
            this.label6 = new System.Windows.Forms.Label();
            this.radioButton9 = new System.Windows.Forms.RadioButton();
            this.radioButton10 = new System.Windows.Forms.RadioButton();
            this.radioButton11 = new System.Windows.Forms.RadioButton();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.radioButton12 = new System.Windows.Forms.RadioButton();
            this.radioButton13 = new System.Windows.Forms.RadioButton();
            this.radioButton14 = new System.Windows.Forms.RadioButton();
            this.label9 = new System.Windows.Forms.Label();
            this.radioButton15 = new System.Windows.Forms.RadioButton();
            this.radioButton16 = new System.Windows.Forms.RadioButton();
            this.radioButton17 = new System.Windows.Forms.RadioButton();
            this.label10 = new System.Windows.Forms.Label();
            this.radioButton18 = new System.Windows.Forms.RadioButton();
            this.radioButton19 = new System.Windows.Forms.RadioButton();
            this.radioButton20 = new System.Windows.Forms.RadioButton();
            this.label11 = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.radioButton21 = new System.Windows.Forms.RadioButton();
            this.radioButton22 = new System.Windows.Forms.RadioButton();
            this.radioButton23 = new System.Windows.Forms.RadioButton();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.label16 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Showcard Gothic", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label1.ForeColor = System.Drawing.Color.LightGreen;
            this.label1.Location = new System.Drawing.Point(418, 37);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(380, 37);
            this.label1.TabIndex = 0;
            this.label1.Text = "Security Parameters";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // textBox1
            // 
            this.textBox1.BackColor = System.Drawing.Color.LightGreen;
            this.textBox1.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.textBox1.Font = new System.Drawing.Font("Segoe UI Symbol", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.textBox1.Location = new System.Drawing.Point(101, 238);
            this.textBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(260, 34);
            this.textBox1.TabIndex = 1;
            this.textBox1.Text = "Enter Function Name";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Showcard Gothic", 14.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label2.ForeColor = System.Drawing.Color.LightGreen;
            this.label2.Location = new System.Drawing.Point(101, 172);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(248, 30);
            this.label2.TabIndex = 2;
            this.label2.Text = "WinApi Functions";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // radioButton1
            // 
            this.radioButton1.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton1.AutoSize = true;
            this.radioButton1.BackColor = System.Drawing.Color.Orange;
            this.radioButton1.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton1.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton1.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton1.ForeColor = System.Drawing.Color.Black;
            this.radioButton1.Location = new System.Drawing.Point(387, 238);
            this.radioButton1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton1.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton1.MinimumSize = new System.Drawing.Size(31, 36);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(31, 36);
            this.radioButton1.TabIndex = 3;
            this.radioButton1.TabStop = true;
            this.radioButton1.UseVisualStyleBackColor = false;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // radioButton2
            // 
            this.radioButton2.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton2.AutoSize = true;
            this.radioButton2.BackColor = System.Drawing.Color.Firebrick;
            this.radioButton2.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton2.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton2.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton2.ForeColor = System.Drawing.Color.Black;
            this.radioButton2.Location = new System.Drawing.Point(446, 238);
            this.radioButton2.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton2.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton2.MinimumSize = new System.Drawing.Size(31, 36);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(31, 36);
            this.radioButton2.TabIndex = 4;
            this.radioButton2.TabStop = true;
            this.radioButton2.UseVisualStyleBackColor = false;
            this.radioButton2.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.Black;
            this.button1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.button1.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.button1.ForeColor = System.Drawing.Color.LightGreen;
            this.button1.Location = new System.Drawing.Point(101, 282);
            this.button1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(61, 33);
            this.button1.TabIndex = 5;
            this.button1.Text = "add";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // listBox1
            // 
            this.listBox1.BackColor = System.Drawing.Color.Black;
            this.listBox1.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawVariable;
            this.listBox1.Font = new System.Drawing.Font("Segoe UI Symbol", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.listBox1.ForeColor = System.Drawing.Color.LightGreen;
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 20;
            this.listBox1.Location = new System.Drawing.Point(101, 336);
            this.listBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(260, 164);
            this.listBox1.TabIndex = 6;
            this.listBox1.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.ListBox_DrawItem);
            this.listBox1.MeasureItem += new System.Windows.Forms.MeasureItemEventHandler(this.MyListBox_MeasureItem);
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged_1);
            this.listBox1.DoubleClick += new System.EventHandler(this.listBox1_DoubleClick);
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.Black;
            this.button2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.button2.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.button2.ForeColor = System.Drawing.Color.LightGreen;
            this.button2.Location = new System.Drawing.Point(101, 510);
            this.button2.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(79, 36);
            this.button2.TabIndex = 7;
            this.button2.Text = "Clear";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(782, 118);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(50, 20);
            this.label3.TabIndex = 8;
            this.label3.Text = "label3";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Showcard Gothic", 14.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label4.ForeColor = System.Drawing.Color.LightGreen;
            this.label4.Location = new System.Drawing.Point(782, 118);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(352, 30);
            this.label4.TabIndex = 9;
            this.label4.Text = "WinApi Function Families";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label5.ForeColor = System.Drawing.Color.LightYellow;
            this.label5.Location = new System.Drawing.Point(885, 184);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(224, 21);
            this.label5.TabIndex = 10;
            this.label5.Text = "File System Functions";
            this.label5.Click += new System.EventHandler(this.label5_Click);
            // 
            // radioButton3
            // 
            this.radioButton3.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton3.AutoSize = true;
            this.radioButton3.BackColor = System.Drawing.Color.Firebrick;
            this.radioButton3.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton3.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton3.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton3.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton3.ForeColor = System.Drawing.Color.Black;
            this.radioButton3.Location = new System.Drawing.Point(859, 184);
            this.radioButton3.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton3.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton3.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(19, 23);
            this.radioButton3.TabIndex = 11;
            this.radioButton3.TabStop = true;
            this.radioButton3.UseVisualStyleBackColor = false;
            this.radioButton3.CheckedChanged += new System.EventHandler(this.radioButton3_CheckedChanged);
            // 
            // radioButton4
            // 
            this.radioButton4.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton4.AutoSize = true;
            this.radioButton4.BackColor = System.Drawing.Color.LimeGreen;
            this.radioButton4.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton4.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton4.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton4.Font = new System.Drawing.Font("Showcard Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton4.ForeColor = System.Drawing.Color.Black;
            this.radioButton4.Location = new System.Drawing.Point(806, 184);
            this.radioButton4.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton4.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton4.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton4.Name = "radioButton4";
            this.radioButton4.Size = new System.Drawing.Size(19, 23);
            this.radioButton4.TabIndex = 12;
            this.radioButton4.TabStop = true;
            this.radioButton4.UseVisualStyleBackColor = false;
            this.radioButton4.CheckedChanged += new System.EventHandler(this.radioButton4_CheckedChanged);
            // 
            // radioButton5
            // 
            this.radioButton5.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton5.AutoSize = true;
            this.radioButton5.BackColor = System.Drawing.Color.Orange;
            this.radioButton5.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton5.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton5.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton5.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton5.ForeColor = System.Drawing.Color.Black;
            this.radioButton5.Location = new System.Drawing.Point(833, 184);
            this.radioButton5.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton5.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton5.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton5.Name = "radioButton5";
            this.radioButton5.Size = new System.Drawing.Size(19, 23);
            this.radioButton5.TabIndex = 13;
            this.radioButton5.TabStop = true;
            this.radioButton5.UseVisualStyleBackColor = false;
            this.radioButton5.CheckedChanged += new System.EventHandler(this.radioButton5_CheckedChanged);
            // 
            // radioButton6
            // 
            this.radioButton6.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton6.AutoSize = true;
            this.radioButton6.BackColor = System.Drawing.Color.Orange;
            this.radioButton6.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton6.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton6.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton6.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton6.ForeColor = System.Drawing.Color.Black;
            this.radioButton6.Location = new System.Drawing.Point(833, 233);
            this.radioButton6.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton6.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton6.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton6.Name = "radioButton6";
            this.radioButton6.Size = new System.Drawing.Size(19, 23);
            this.radioButton6.TabIndex = 17;
            this.radioButton6.TabStop = true;
            this.radioButton6.UseVisualStyleBackColor = false;
            this.radioButton6.CheckedChanged += new System.EventHandler(this.radioButton6_CheckedChanged);
            // 
            // radioButton7
            // 
            this.radioButton7.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton7.AutoSize = true;
            this.radioButton7.BackColor = System.Drawing.Color.LimeGreen;
            this.radioButton7.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton7.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton7.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton7.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton7.ForeColor = System.Drawing.Color.Black;
            this.radioButton7.Location = new System.Drawing.Point(806, 233);
            this.radioButton7.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton7.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton7.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton7.Name = "radioButton7";
            this.radioButton7.Size = new System.Drawing.Size(19, 23);
            this.radioButton7.TabIndex = 16;
            this.radioButton7.TabStop = true;
            this.radioButton7.UseVisualStyleBackColor = false;
            this.radioButton7.CheckedChanged += new System.EventHandler(this.radioButton7_CheckedChanged);
            // 
            // radioButton8
            // 
            this.radioButton8.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton8.AutoSize = true;
            this.radioButton8.BackColor = System.Drawing.Color.Firebrick;
            this.radioButton8.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton8.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton8.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton8.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton8.ForeColor = System.Drawing.Color.Black;
            this.radioButton8.Location = new System.Drawing.Point(859, 233);
            this.radioButton8.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton8.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton8.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton8.Name = "radioButton8";
            this.radioButton8.Size = new System.Drawing.Size(19, 23);
            this.radioButton8.TabIndex = 15;
            this.radioButton8.TabStop = true;
            this.radioButton8.UseVisualStyleBackColor = false;
            this.radioButton8.CheckedChanged += new System.EventHandler(this.radioButton8_CheckedChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label6.ForeColor = System.Drawing.Color.LightYellow;
            this.label6.Location = new System.Drawing.Point(885, 233);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(266, 21);
            this.label6.TabIndex = 14;
            this.label6.Text = "Communication Functions";
            // 
            // radioButton9
            // 
            this.radioButton9.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton9.AutoSize = true;
            this.radioButton9.BackColor = System.Drawing.Color.Orange;
            this.radioButton9.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton9.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton9.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton9.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton9.ForeColor = System.Drawing.Color.Black;
            this.radioButton9.Location = new System.Drawing.Point(833, 282);
            this.radioButton9.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton9.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton9.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton9.Name = "radioButton9";
            this.radioButton9.Size = new System.Drawing.Size(19, 23);
            this.radioButton9.TabIndex = 21;
            this.radioButton9.TabStop = true;
            this.radioButton9.UseVisualStyleBackColor = false;
            this.radioButton9.CheckedChanged += new System.EventHandler(this.radioButton9_CheckedChanged);
            // 
            // radioButton10
            // 
            this.radioButton10.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton10.AutoSize = true;
            this.radioButton10.BackColor = System.Drawing.Color.LimeGreen;
            this.radioButton10.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton10.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton10.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton10.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton10.ForeColor = System.Drawing.Color.Black;
            this.radioButton10.Location = new System.Drawing.Point(806, 282);
            this.radioButton10.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton10.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton10.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton10.Name = "radioButton10";
            this.radioButton10.Size = new System.Drawing.Size(19, 23);
            this.radioButton10.TabIndex = 20;
            this.radioButton10.TabStop = true;
            this.radioButton10.UseVisualStyleBackColor = false;
            this.radioButton10.CheckedChanged += new System.EventHandler(this.radioButton10_CheckedChanged);
            // 
            // radioButton11
            // 
            this.radioButton11.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton11.AutoSize = true;
            this.radioButton11.BackColor = System.Drawing.Color.Firebrick;
            this.radioButton11.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton11.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton11.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton11.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton11.ForeColor = System.Drawing.Color.Black;
            this.radioButton11.Location = new System.Drawing.Point(859, 282);
            this.radioButton11.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton11.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton11.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton11.Name = "radioButton11";
            this.radioButton11.Size = new System.Drawing.Size(19, 23);
            this.radioButton11.TabIndex = 19;
            this.radioButton11.TabStop = true;
            this.radioButton11.UseVisualStyleBackColor = false;
            this.radioButton11.CheckedChanged += new System.EventHandler(this.radioButton11_CheckedChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label7.ForeColor = System.Drawing.Color.LightYellow;
            this.label7.Location = new System.Drawing.Point(885, 282);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(203, 21);
            this.label7.TabIndex = 18;
            this.label7.Text = "Registry Functions";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Showcard Gothic", 14.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label8.ForeColor = System.Drawing.Color.LightGreen;
            this.label8.Location = new System.Drawing.Point(782, 365);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(210, 30);
            this.label8.TabIndex = 22;
            this.label8.Text = "Drivers to use";
            // 
            // radioButton12
            // 
            this.radioButton12.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton12.AutoSize = true;
            this.radioButton12.BackColor = System.Drawing.Color.Orange;
            this.radioButton12.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton12.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton12.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton12.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton12.ForeColor = System.Drawing.Color.Black;
            this.radioButton12.Location = new System.Drawing.Point(833, 509);
            this.radioButton12.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton12.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton12.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton12.Name = "radioButton12";
            this.radioButton12.Size = new System.Drawing.Size(19, 23);
            this.radioButton12.TabIndex = 34;
            this.radioButton12.TabStop = true;
            this.radioButton12.UseVisualStyleBackColor = false;
            this.radioButton12.CheckedChanged += new System.EventHandler(this.radioButton12_CheckedChanged);
            // 
            // radioButton13
            // 
            this.radioButton13.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton13.AutoSize = true;
            this.radioButton13.BackColor = System.Drawing.Color.LimeGreen;
            this.radioButton13.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton13.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton13.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton13.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton13.ForeColor = System.Drawing.Color.Black;
            this.radioButton13.Location = new System.Drawing.Point(806, 509);
            this.radioButton13.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton13.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton13.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton13.Name = "radioButton13";
            this.radioButton13.Size = new System.Drawing.Size(19, 23);
            this.radioButton13.TabIndex = 33;
            this.radioButton13.TabStop = true;
            this.radioButton13.UseVisualStyleBackColor = false;
            this.radioButton13.CheckedChanged += new System.EventHandler(this.radioButton13_CheckedChanged);
            // 
            // radioButton14
            // 
            this.radioButton14.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton14.AutoSize = true;
            this.radioButton14.BackColor = System.Drawing.Color.Firebrick;
            this.radioButton14.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton14.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton14.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton14.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton14.ForeColor = System.Drawing.Color.Black;
            this.radioButton14.Location = new System.Drawing.Point(859, 509);
            this.radioButton14.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton14.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton14.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton14.Name = "radioButton14";
            this.radioButton14.Size = new System.Drawing.Size(19, 23);
            this.radioButton14.TabIndex = 32;
            this.radioButton14.TabStop = true;
            this.radioButton14.UseVisualStyleBackColor = false;
            this.radioButton14.CheckedChanged += new System.EventHandler(this.radioButton14_CheckedChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label9.ForeColor = System.Drawing.Color.LightYellow;
            this.label9.Location = new System.Drawing.Point(885, 509);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(243, 21);
            this.label9.TabIndex = 31;
            this.label9.Text = "Process/Thread driver";
            // 
            // radioButton15
            // 
            this.radioButton15.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton15.AutoSize = true;
            this.radioButton15.BackColor = System.Drawing.Color.Orange;
            this.radioButton15.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton15.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton15.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton15.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton15.ForeColor = System.Drawing.Color.Black;
            this.radioButton15.Location = new System.Drawing.Point(833, 460);
            this.radioButton15.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton15.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton15.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton15.Name = "radioButton15";
            this.radioButton15.Size = new System.Drawing.Size(19, 23);
            this.radioButton15.TabIndex = 30;
            this.radioButton15.TabStop = true;
            this.radioButton15.UseVisualStyleBackColor = false;
            this.radioButton15.CheckedChanged += new System.EventHandler(this.radioButton15_CheckedChanged);
            // 
            // radioButton16
            // 
            this.radioButton16.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton16.AutoSize = true;
            this.radioButton16.BackColor = System.Drawing.Color.LimeGreen;
            this.radioButton16.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton16.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton16.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton16.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton16.ForeColor = System.Drawing.Color.Black;
            this.radioButton16.Location = new System.Drawing.Point(806, 460);
            this.radioButton16.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton16.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton16.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton16.Name = "radioButton16";
            this.radioButton16.Size = new System.Drawing.Size(19, 23);
            this.radioButton16.TabIndex = 29;
            this.radioButton16.TabStop = true;
            this.radioButton16.UseVisualStyleBackColor = false;
            this.radioButton16.CheckedChanged += new System.EventHandler(this.radioButton16_CheckedChanged);
            // 
            // radioButton17
            // 
            this.radioButton17.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton17.AutoSize = true;
            this.radioButton17.BackColor = System.Drawing.Color.Firebrick;
            this.radioButton17.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton17.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton17.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton17.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton17.ForeColor = System.Drawing.Color.Black;
            this.radioButton17.Location = new System.Drawing.Point(859, 460);
            this.radioButton17.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton17.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton17.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton17.Name = "radioButton17";
            this.radioButton17.Size = new System.Drawing.Size(19, 23);
            this.radioButton17.TabIndex = 28;
            this.radioButton17.TabStop = true;
            this.radioButton17.UseVisualStyleBackColor = false;
            this.radioButton17.CheckedChanged += new System.EventHandler(this.radioButton17_CheckedChanged);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label10.ForeColor = System.Drawing.Color.LightYellow;
            this.label10.Location = new System.Drawing.Point(885, 460);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(236, 21);
            this.label10.TabIndex = 27;
            this.label10.Text = "Communication Driver";
            // 
            // radioButton18
            // 
            this.radioButton18.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton18.AutoSize = true;
            this.radioButton18.BackColor = System.Drawing.Color.Orange;
            this.radioButton18.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton18.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton18.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton18.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton18.ForeColor = System.Drawing.Color.Black;
            this.radioButton18.Location = new System.Drawing.Point(833, 410);
            this.radioButton18.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton18.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton18.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton18.Name = "radioButton18";
            this.radioButton18.Size = new System.Drawing.Size(19, 23);
            this.radioButton18.TabIndex = 26;
            this.radioButton18.TabStop = true;
            this.radioButton18.UseVisualStyleBackColor = false;
            this.radioButton18.CheckedChanged += new System.EventHandler(this.radioButton18_CheckedChanged);
            // 
            // radioButton19
            // 
            this.radioButton19.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton19.AutoSize = true;
            this.radioButton19.BackColor = System.Drawing.Color.LimeGreen;
            this.radioButton19.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton19.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton19.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton19.Font = new System.Drawing.Font("Showcard Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton19.ForeColor = System.Drawing.Color.Black;
            this.radioButton19.Location = new System.Drawing.Point(806, 410);
            this.radioButton19.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton19.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton19.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton19.Name = "radioButton19";
            this.radioButton19.Size = new System.Drawing.Size(19, 23);
            this.radioButton19.TabIndex = 25;
            this.radioButton19.TabStop = true;
            this.radioButton19.UseVisualStyleBackColor = false;
            this.radioButton19.CheckedChanged += new System.EventHandler(this.radioButton19_CheckedChanged);
            // 
            // radioButton20
            // 
            this.radioButton20.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton20.AutoSize = true;
            this.radioButton20.BackColor = System.Drawing.Color.Firebrick;
            this.radioButton20.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton20.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton20.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton20.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton20.ForeColor = System.Drawing.Color.Black;
            this.radioButton20.Location = new System.Drawing.Point(859, 410);
            this.radioButton20.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton20.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton20.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton20.Name = "radioButton20";
            this.radioButton20.Size = new System.Drawing.Size(19, 23);
            this.radioButton20.TabIndex = 24;
            this.radioButton20.TabStop = true;
            this.radioButton20.UseVisualStyleBackColor = false;
            this.radioButton20.CheckedChanged += new System.EventHandler(this.radioButton20_CheckedChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label11.ForeColor = System.Drawing.Color.LightYellow;
            this.label11.Location = new System.Drawing.Point(885, 410);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(194, 21);
            this.label11.TabIndex = 23;
            this.label11.Text = "File System Driver";
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.Color.Black;
            this.button3.Cursor = System.Windows.Forms.Cursors.Hand;
            this.button3.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.button3.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.button3.ForeColor = System.Drawing.Color.LightGreen;
            this.button3.Location = new System.Drawing.Point(1023, 630);
            this.button3.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(128, 40);
            this.button3.TabIndex = 35;
            this.button3.Text = "continue";
            this.button3.UseVisualStyleBackColor = false;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // radioButton21
            // 
            this.radioButton21.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton21.AutoSize = true;
            this.radioButton21.BackColor = System.Drawing.Color.Orange;
            this.radioButton21.Enabled = false;
            this.radioButton21.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton21.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton21.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton21.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton21.ForeColor = System.Drawing.Color.Black;
            this.radioButton21.Location = new System.Drawing.Point(24, 84);
            this.radioButton21.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton21.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton21.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton21.Name = "radioButton21";
            this.radioButton21.Size = new System.Drawing.Size(19, 23);
            this.radioButton21.TabIndex = 38;
            this.radioButton21.TabStop = true;
            this.radioButton21.UseVisualStyleBackColor = false;
            // 
            // radioButton22
            // 
            this.radioButton22.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton22.AutoSize = true;
            this.radioButton22.BackColor = System.Drawing.Color.LimeGreen;
            this.radioButton22.Enabled = false;
            this.radioButton22.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton22.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton22.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton22.Font = new System.Drawing.Font("Showcard Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton22.ForeColor = System.Drawing.Color.Black;
            this.radioButton22.Location = new System.Drawing.Point(24, 53);
            this.radioButton22.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton22.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton22.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton22.Name = "radioButton22";
            this.radioButton22.Size = new System.Drawing.Size(19, 23);
            this.radioButton22.TabIndex = 37;
            this.radioButton22.TabStop = true;
            this.radioButton22.UseVisualStyleBackColor = false;
            // 
            // radioButton23
            // 
            this.radioButton23.Appearance = System.Windows.Forms.Appearance.Button;
            this.radioButton23.AutoSize = true;
            this.radioButton23.BackColor = System.Drawing.Color.Firebrick;
            this.radioButton23.Enabled = false;
            this.radioButton23.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.radioButton23.FlatAppearance.CheckedBackColor = System.Drawing.Color.Black;
            this.radioButton23.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.radioButton23.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.radioButton23.ForeColor = System.Drawing.Color.Black;
            this.radioButton23.Location = new System.Drawing.Point(24, 116);
            this.radioButton23.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.radioButton23.MaximumSize = new System.Drawing.Size(11, 13);
            this.radioButton23.MinimumSize = new System.Drawing.Size(19, 23);
            this.radioButton23.Name = "radioButton23";
            this.radioButton23.Size = new System.Drawing.Size(19, 23);
            this.radioButton23.TabIndex = 36;
            this.radioButton23.TabStop = true;
            this.radioButton23.UseVisualStyleBackColor = false;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label12.ForeColor = System.Drawing.Color.LightYellow;
            this.label12.Location = new System.Drawing.Point(62, 116);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(69, 21);
            this.label12.TabIndex = 39;
            this.label12.Text = "Block";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label13.ForeColor = System.Drawing.Color.LightYellow;
            this.label13.Location = new System.Drawing.Point(62, 85);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(65, 21);
            this.label13.TabIndex = 40;
            this.label13.Text = "Warn";
            this.label13.Click += new System.EventHandler(this.label13_Click);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Showcard Gothic", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label14.ForeColor = System.Drawing.Color.LightYellow;
            this.label14.Location = new System.Drawing.Point(62, 53);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(53, 21);
            this.label14.TabIndex = 41;
            this.label14.Text = "Pass";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Showcard Gothic", 14.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label15.ForeColor = System.Drawing.Color.LightGreen;
            this.label15.Location = new System.Drawing.Point(3, 12);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(233, 30);
            this.label15.TabIndex = 42;
            this.label15.Text = "Parameters key";
            // 
            // button4
            // 
            this.button4.BackColor = System.Drawing.Color.Black;
            this.button4.Cursor = System.Windows.Forms.Cursors.Hand;
            this.button4.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.button4.Font = new System.Drawing.Font("Showcard Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.button4.ForeColor = System.Drawing.Color.LightGreen;
            this.button4.Location = new System.Drawing.Point(24, 630);
            this.button4.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(114, 40);
            this.button4.TabIndex = 43;
            this.button4.Text = "back";
            this.button4.UseVisualStyleBackColor = false;
            // 
            // trackBar1
            // 
            this.trackBar1.AutoSize = false;
            this.trackBar1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.trackBar1.Location = new System.Drawing.Point(267, 582);
            this.trackBar1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.trackBar1.Maximum = 100;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(384, 60);
            this.trackBar1.TabIndex = 44;
            this.trackBar1.TickFrequency = 10;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            this.trackBar1.ValueChanged += new System.EventHandler(this.trackBar1_ValueChanged);
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("Showcard Gothic", 14.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point);
            this.label16.ForeColor = System.Drawing.Color.LightGreen;
            this.label16.Location = new System.Drawing.Point(657, 582);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(269, 30);
            this.label16.TabIndex = 45;
            this.label16.Text = "RAM allowed: 0 MB";
            this.label16.Click += new System.EventHandler(this.label16_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Desktop;
            this.ClientSize = new System.Drawing.Size(1188, 689);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.radioButton21);
            this.Controls.Add(this.radioButton22);
            this.Controls.Add(this.radioButton23);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.radioButton12);
            this.Controls.Add(this.radioButton13);
            this.Controls.Add(this.radioButton14);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.radioButton15);
            this.Controls.Add(this.radioButton16);
            this.Controls.Add(this.radioButton17);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.radioButton18);
            this.Controls.Add(this.radioButton19);
            this.Controls.Add(this.radioButton20);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.radioButton9);
            this.Controls.Add(this.radioButton10);
            this.Controls.Add(this.radioButton11);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.radioButton6);
            this.Controls.Add(this.radioButton7);
            this.Controls.Add(this.radioButton8);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.radioButton5);
            this.Controls.Add(this.radioButton4);
            this.Controls.Add(this.radioButton3);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.radioButton2);
            this.Controls.Add(this.radioButton1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label1);
            this.ForeColor = System.Drawing.Color.LightGreen;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "Form2";
            this.Text = "Form2";
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        private void ListBox1_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            throw new NotImplementedException();
        }

        #endregion

        private Label label1;
        private TextBox textBox1;
        private Label label2;
        private RadioButton radioButton1;
        private RadioButton radioButton2;
        private Button button1;
        private ListBox listBox1;
        private Button button2;
        private Label label3;
        private Label label4;
        private Label label5;
        private RadioButton radioButton3;
        private RadioButton radioButton4;
        private RadioButton radioButton5;
        private RadioButton radioButton6;
        private RadioButton radioButton7;
        private RadioButton radioButton8;
        private Label label6;
        private RadioButton radioButton9;
        private RadioButton radioButton10;
        private RadioButton radioButton11;
        private Label label7;
        private Label label8;
        private RadioButton radioButton12;
        private RadioButton radioButton13;
        private RadioButton radioButton14;
        private Label label9;
        private RadioButton radioButton15;
        private RadioButton radioButton16;
        private RadioButton radioButton17;
        private Label label10;
        private RadioButton radioButton18;
        private RadioButton radioButton19;
        private RadioButton radioButton20;
        private Label label11;
        private Button button3;
        private RadioButton radioButton21;
        private RadioButton radioButton22;
        private RadioButton radioButton23;
        private Label label12;
        private Label label13;
        private Label label14;
        private Label label15;
        private Button button4;
        private TrackBar trackBar1;
        private Label label16;
    }
}