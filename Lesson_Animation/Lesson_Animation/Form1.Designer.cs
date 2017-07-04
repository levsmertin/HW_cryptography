namespace Lesson_Animation
{
    partial class Form1
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.button1 = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.Obs = new System.Windows.Forms.ListBox();
            this.elements = new System.Windows.Forms.ListBox();
            this.end_obs = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.Oa = new System.Windows.Forms.TextBox();
            this.Oy = new System.Windows.Forms.TextBox();
            this.Ox = new System.Windows.Forms.TextBox();
            this.remObs = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.Re = new System.Windows.Forms.TextBox();
            this.Ye = new System.Windows.Forms.TextBox();
            this.Xe = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.Rote = new System.Windows.Forms.TextBox();
            this.interva_ = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(12, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(524, 376);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 394);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(91, 62);
            this.button1.TabIndex = 1;
            this.button1.Text = "Go";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 20;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Obs
            // 
            this.Obs.FormattingEnabled = true;
            this.Obs.Location = new System.Drawing.Point(552, 12);
            this.Obs.Name = "Obs";
            this.Obs.Size = new System.Drawing.Size(479, 95);
            this.Obs.TabIndex = 2;
            // 
            // elements
            // 
            this.elements.FormattingEnabled = true;
            this.elements.Location = new System.Drawing.Point(552, 180);
            this.elements.Name = "elements";
            this.elements.Size = new System.Drawing.Size(479, 95);
            this.elements.TabIndex = 3;
            // 
            // end_obs
            // 
            this.end_obs.Location = new System.Drawing.Point(744, 123);
            this.end_obs.Name = "end_obs";
            this.end_obs.Size = new System.Drawing.Size(83, 23);
            this.end_obs.TabIndex = 4;
            this.end_obs.Text = "Добавить";
            this.end_obs.UseVisualStyleBackColor = true;
            this.end_obs.Click += new System.EventHandler(this.end_obs_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(663, 110);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(14, 13);
            this.label3.TabIndex = 15;
            this.label3.Text = "A";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(609, 110);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(14, 13);
            this.label2.TabIndex = 14;
            this.label2.Text = "Y";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(549, 110);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(14, 13);
            this.label1.TabIndex = 13;
            this.label1.Text = "X";
            // 
            // Oa
            // 
            this.Oa.Location = new System.Drawing.Point(666, 126);
            this.Oa.Name = "Oa";
            this.Oa.Size = new System.Drawing.Size(72, 20);
            this.Oa.TabIndex = 12;
            // 
            // Oy
            // 
            this.Oy.Location = new System.Drawing.Point(609, 126);
            this.Oy.Name = "Oy";
            this.Oy.Size = new System.Drawing.Size(51, 20);
            this.Oy.TabIndex = 11;
            // 
            // Ox
            // 
            this.Ox.Location = new System.Drawing.Point(552, 126);
            this.Ox.Name = "Ox";
            this.Ox.Size = new System.Drawing.Size(51, 20);
            this.Ox.TabIndex = 10;
            // 
            // remObs
            // 
            this.remObs.Location = new System.Drawing.Point(833, 123);
            this.remObs.Name = "remObs";
            this.remObs.Size = new System.Drawing.Size(26, 23);
            this.remObs.TabIndex = 16;
            this.remObs.Text = "X";
            this.remObs.UseVisualStyleBackColor = true;
            this.remObs.Click += new System.EventHandler(this.remObs_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(912, 293);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(26, 23);
            this.button2.TabIndex = 24;
            this.button2.Text = "X";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(663, 280);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(15, 13);
            this.label4.TabIndex = 23;
            this.label4.Text = "R";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(609, 280);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(14, 13);
            this.label5.TabIndex = 22;
            this.label5.Text = "Y";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(549, 280);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(14, 13);
            this.label6.TabIndex = 21;
            this.label6.Text = "X";
            // 
            // Re
            // 
            this.Re.Location = new System.Drawing.Point(666, 296);
            this.Re.Name = "Re";
            this.Re.Size = new System.Drawing.Size(72, 20);
            this.Re.TabIndex = 20;
            // 
            // Ye
            // 
            this.Ye.Location = new System.Drawing.Point(609, 296);
            this.Ye.Name = "Ye";
            this.Ye.Size = new System.Drawing.Size(51, 20);
            this.Ye.TabIndex = 19;
            // 
            // Xe
            // 
            this.Xe.Location = new System.Drawing.Point(552, 296);
            this.Xe.Name = "Xe";
            this.Xe.Size = new System.Drawing.Size(51, 20);
            this.Xe.TabIndex = 18;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(823, 293);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(83, 23);
            this.button3.TabIndex = 17;
            this.button3.Text = "Добавить";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(742, 280);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(75, 13);
            this.label7.TabIndex = 26;
            this.label7.Text = "Направление";
            // 
            // Rote
            // 
            this.Rote.Location = new System.Drawing.Point(744, 296);
            this.Rote.Name = "Rote";
            this.Rote.Size = new System.Drawing.Size(72, 20);
            this.Rote.TabIndex = 25;
            // 
            // interva_
            // 
            this.interva_.Location = new System.Drawing.Point(124, 416);
            this.interva_.Name = "interva_";
            this.interva_.Size = new System.Drawing.Size(51, 20);
            this.interva_.TabIndex = 27;
            this.interva_.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(121, 400);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(55, 13);
            this.label8.TabIndex = 28;
            this.label8.Text = "Скорость";
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(181, 416);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(50, 20);
            this.button4.TabIndex = 29;
            this.button4.Text = "OK";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1078, 477);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.interva_);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.Rote);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.Re);
            this.Controls.Add(this.Ye);
            this.Controls.Add(this.Xe);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.remObs);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Oa);
            this.Controls.Add(this.Oy);
            this.Controls.Add(this.Ox);
            this.Controls.Add(this.end_obs);
            this.Controls.Add(this.elements);
            this.Controls.Add(this.Obs);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.pictureBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ListBox Obs;
        private System.Windows.Forms.ListBox elements;
        private System.Windows.Forms.Button end_obs;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Oa;
        private System.Windows.Forms.TextBox Oy;
        private System.Windows.Forms.TextBox Ox;
        private System.Windows.Forms.Button remObs;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox Re;
        private System.Windows.Forms.TextBox Ye;
        private System.Windows.Forms.TextBox Xe;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox Rote;
        private System.Windows.Forms.TextBox interva_;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button button4;
    }
}

