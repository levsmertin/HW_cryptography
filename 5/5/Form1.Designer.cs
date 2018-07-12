namespace _5
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
            this.pictur = new System.Windows.Forms.PictureBox();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictur)).BeginInit();
            this.SuspendLayout();
            // 
            // pictur
            // 
            this.pictur.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.pictur.Location = new System.Drawing.Point(3, 2);
            this.pictur.Name = "pictur";
            this.pictur.Size = new System.Drawing.Size(516, 626);
            this.pictur.TabIndex = 0;
            this.pictur.TabStop = false;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(525, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(115, 65);
            this.button1.TabIndex = 1;
            this.button1.Text = "Go";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1037, 632);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.pictur);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictur)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pictur;
        private System.Windows.Forms.Button button1;
    }
}

