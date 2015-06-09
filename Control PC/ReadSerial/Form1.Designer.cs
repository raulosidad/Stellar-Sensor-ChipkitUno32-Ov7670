namespace ReadSerial
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador requerida.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén utilizando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben eliminar; false en caso contrario, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido del método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
          this.components = new System.ComponentModel.Container();
          System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
          this.textBox1 = new System.Windows.Forms.TextBox();
          this.pictureBox1 = new System.Windows.Forms.PictureBox();
          this.btn_Prueba = new System.Windows.Forms.Button();
          this.btn_Send = new System.Windows.Forms.Button();
          this.btn_Receive = new System.Windows.Forms.Button();
          this.btn_CameraConfig = new System.Windows.Forms.Button();
          this.btn_Clear = new System.Windows.Forms.Button();
          this.btn_ReadHeader = new System.Windows.Forms.Button();
          this.btn_ReadStarPair = new System.Windows.Forms.Button();
          this.Num = new System.Windows.Forms.NumericUpDown();
          this.hEADERBindingSource = new System.Windows.Forms.BindingSource(this.components);
          this.hEADERBindingSource1 = new System.Windows.Forms.BindingSource(this.components);
          this.btn_ReadStarID = new System.Windows.Forms.Button();
          this.btn_ReadUvector = new System.Windows.Forms.Button();
          this.btn_SendHeader = new System.Windows.Forms.Button();
          this.btn_SendStarPairs = new System.Windows.Forms.Button();
          this.btn_SendStarIDs = new System.Windows.Forms.Button();
          this.btn_SendUvectors = new System.Windows.Forms.Button();
          this.groupBox1 = new System.Windows.Forms.GroupBox();
          this.label1 = new System.Windows.Forms.Label();
          this.groupBox2 = new System.Windows.Forms.GroupBox();
          this.Manual = new System.Windows.Forms.RadioButton();
          this.groupBox3 = new System.Windows.Forms.GroupBox();
          this.StarTracker = new System.Windows.Forms.RadioButton();
          ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
          ((System.ComponentModel.ISupportInitialize)(this.Num)).BeginInit();
          ((System.ComponentModel.ISupportInitialize)(this.hEADERBindingSource)).BeginInit();
          ((System.ComponentModel.ISupportInitialize)(this.hEADERBindingSource1)).BeginInit();
          this.groupBox1.SuspendLayout();
          this.groupBox2.SuspendLayout();
          this.groupBox3.SuspendLayout();
          this.SuspendLayout();
          // 
          // textBox1
          // 
          this.textBox1.Location = new System.Drawing.Point(1, 0);
          this.textBox1.Multiline = true;
          this.textBox1.Name = "textBox1";
          this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
          this.textBox1.Size = new System.Drawing.Size(461, 586);
          this.textBox1.TabIndex = 0;
          // 
          // pictureBox1
          // 
          this.pictureBox1.BackColor = System.Drawing.SystemColors.ButtonHighlight;
          this.pictureBox1.Location = new System.Drawing.Point(490, 26);
          this.pictureBox1.Name = "pictureBox1";
          this.pictureBox1.Size = new System.Drawing.Size(480, 360);
          this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
          this.pictureBox1.TabIndex = 1;
          this.pictureBox1.TabStop = false;
          // 
          // btn_Prueba
          // 
          this.btn_Prueba.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_Prueba.Location = new System.Drawing.Point(1008, 220);
          this.btn_Prueba.Name = "btn_Prueba";
          this.btn_Prueba.Size = new System.Drawing.Size(201, 52);
          this.btn_Prueba.TabIndex = 2;
          this.btn_Prueba.Text = "Prueba...";
          this.btn_Prueba.UseVisualStyleBackColor = true;
          this.btn_Prueba.Visible = false;
          this.btn_Prueba.Click += new System.EventHandler(this.btn_Prueba_Click);
          // 
          // btn_Send
          // 
          this.btn_Send.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_Send.Location = new System.Drawing.Point(1003, 28);
          this.btn_Send.Name = "btn_Send";
          this.btn_Send.Size = new System.Drawing.Size(201, 46);
          this.btn_Send.TabIndex = 4;
          this.btn_Send.Text = "Capture Image";
          this.btn_Send.UseVisualStyleBackColor = true;
          this.btn_Send.Click += new System.EventHandler(this.btn_Send_Click);
          // 
          // btn_Receive
          // 
          this.btn_Receive.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_Receive.Location = new System.Drawing.Point(1003, 90);
          this.btn_Receive.Name = "btn_Receive";
          this.btn_Receive.Size = new System.Drawing.Size(201, 46);
          this.btn_Receive.TabIndex = 5;
          this.btn_Receive.Text = "Read Image";
          this.btn_Receive.UseVisualStyleBackColor = true;
          this.btn_Receive.Click += new System.EventHandler(this.btn_Receive_Click);
          // 
          // btn_CameraConfig
          // 
          this.btn_CameraConfig.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_CameraConfig.Location = new System.Drawing.Point(1003, 154);
          this.btn_CameraConfig.Name = "btn_CameraConfig";
          this.btn_CameraConfig.Size = new System.Drawing.Size(201, 49);
          this.btn_CameraConfig.TabIndex = 6;
          this.btn_CameraConfig.Text = "Get Camera Config";
          this.btn_CameraConfig.UseVisualStyleBackColor = true;
          this.btn_CameraConfig.Click += new System.EventHandler(this.btn_CameraConfig_Click);
          // 
          // btn_Clear
          // 
          this.btn_Clear.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_Clear.Location = new System.Drawing.Point(0, 585);
          this.btn_Clear.Name = "btn_Clear";
          this.btn_Clear.Size = new System.Drawing.Size(462, 36);
          this.btn_Clear.TabIndex = 7;
          this.btn_Clear.Text = "CLEAR";
          this.btn_Clear.UseVisualStyleBackColor = true;
          this.btn_Clear.Click += new System.EventHandler(this.btn_Clear_Click);
          // 
          // btn_ReadHeader
          // 
          this.btn_ReadHeader.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_ReadHeader.Location = new System.Drawing.Point(11, 32);
          this.btn_ReadHeader.Name = "btn_ReadHeader";
          this.btn_ReadHeader.Size = new System.Drawing.Size(138, 38);
          this.btn_ReadHeader.TabIndex = 9;
          this.btn_ReadHeader.Text = "Read Header";
          this.btn_ReadHeader.UseVisualStyleBackColor = true;
          this.btn_ReadHeader.Click += new System.EventHandler(this.btn_ReadHeader_Click);
          // 
          // btn_ReadStarPair
          // 
          this.btn_ReadStarPair.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_ReadStarPair.Location = new System.Drawing.Point(172, 32);
          this.btn_ReadStarPair.Name = "btn_ReadStarPair";
          this.btn_ReadStarPair.Size = new System.Drawing.Size(152, 38);
          this.btn_ReadStarPair.TabIndex = 12;
          this.btn_ReadStarPair.Text = "Read Star Pair";
          this.btn_ReadStarPair.UseVisualStyleBackColor = true;
          this.btn_ReadStarPair.Click += new System.EventHandler(this.btn_ReadStarPair_Click);
          // 
          // Num
          // 
          this.Num.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.Num.Location = new System.Drawing.Point(673, 39);
          this.Num.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
          this.Num.Name = "Num";
          this.Num.Size = new System.Drawing.Size(63, 26);
          this.Num.TabIndex = 13;
          // 
          // hEADERBindingSource
          // 
          this.hEADERBindingSource.DataSource = typeof(EEPROM.HEADER);
          // 
          // hEADERBindingSource1
          // 
          this.hEADERBindingSource1.DataSource = typeof(EEPROM.HEADER);
          // 
          // btn_ReadStarID
          // 
          this.btn_ReadStarID.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_ReadStarID.Location = new System.Drawing.Point(353, 32);
          this.btn_ReadStarID.Name = "btn_ReadStarID";
          this.btn_ReadStarID.Size = new System.Drawing.Size(138, 38);
          this.btn_ReadStarID.TabIndex = 12;
          this.btn_ReadStarID.Text = "Read Star ID";
          this.btn_ReadStarID.UseVisualStyleBackColor = true;
          this.btn_ReadStarID.Click += new System.EventHandler(this.btn_ReadStarID_Click);
          // 
          // btn_ReadUvector
          // 
          this.btn_ReadUvector.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_ReadUvector.Location = new System.Drawing.Point(512, 32);
          this.btn_ReadUvector.Name = "btn_ReadUvector";
          this.btn_ReadUvector.Size = new System.Drawing.Size(138, 38);
          this.btn_ReadUvector.TabIndex = 12;
          this.btn_ReadUvector.Text = "Read Uvector";
          this.btn_ReadUvector.UseVisualStyleBackColor = true;
          this.btn_ReadUvector.Click += new System.EventHandler(this.btn_ReadUvector_Click);
          // 
          // btn_SendHeader
          // 
          this.btn_SendHeader.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_SendHeader.Location = new System.Drawing.Point(11, 28);
          this.btn_SendHeader.Name = "btn_SendHeader";
          this.btn_SendHeader.Size = new System.Drawing.Size(138, 35);
          this.btn_SendHeader.TabIndex = 17;
          this.btn_SendHeader.Text = "Send Header";
          this.btn_SendHeader.UseVisualStyleBackColor = true;
          this.btn_SendHeader.Click += new System.EventHandler(this.btn_SendHeader_Click);
          // 
          // btn_SendStarPairs
          // 
          this.btn_SendStarPairs.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_SendStarPairs.Location = new System.Drawing.Point(172, 28);
          this.btn_SendStarPairs.Name = "btn_SendStarPairs";
          this.btn_SendStarPairs.Size = new System.Drawing.Size(152, 35);
          this.btn_SendStarPairs.TabIndex = 18;
          this.btn_SendStarPairs.Text = "Send Star Pairs";
          this.btn_SendStarPairs.UseVisualStyleBackColor = true;
          this.btn_SendStarPairs.Click += new System.EventHandler(this.btn_SendStarPairs_Click);
          // 
          // btn_SendStarIDs
          // 
          this.btn_SendStarIDs.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_SendStarIDs.Location = new System.Drawing.Point(353, 28);
          this.btn_SendStarIDs.Name = "btn_SendStarIDs";
          this.btn_SendStarIDs.Size = new System.Drawing.Size(138, 35);
          this.btn_SendStarIDs.TabIndex = 19;
          this.btn_SendStarIDs.Text = "Send Star IDs";
          this.btn_SendStarIDs.UseVisualStyleBackColor = true;
          this.btn_SendStarIDs.Click += new System.EventHandler(this.btn_SendStarIDs_Click);
          // 
          // btn_SendUvectors
          // 
          this.btn_SendUvectors.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.btn_SendUvectors.Location = new System.Drawing.Point(512, 28);
          this.btn_SendUvectors.Name = "btn_SendUvectors";
          this.btn_SendUvectors.Size = new System.Drawing.Size(138, 35);
          this.btn_SendUvectors.TabIndex = 20;
          this.btn_SendUvectors.Text = "Send Uvectors";
          this.btn_SendUvectors.UseVisualStyleBackColor = true;
          this.btn_SendUvectors.Click += new System.EventHandler(this.btn_SendUvectors_Click);
          // 
          // groupBox1
          // 
          this.groupBox1.Controls.Add(this.label1);
          this.groupBox1.Controls.Add(this.btn_ReadHeader);
          this.groupBox1.Controls.Add(this.btn_ReadStarID);
          this.groupBox1.Controls.Add(this.btn_ReadStarPair);
          this.groupBox1.Controls.Add(this.btn_ReadUvector);
          this.groupBox1.Controls.Add(this.Num);
          this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.groupBox1.Location = new System.Drawing.Point(468, 495);
          this.groupBox1.Name = "groupBox1";
          this.groupBox1.Size = new System.Drawing.Size(760, 91);
          this.groupBox1.TabIndex = 21;
          this.groupBox1.TabStop = false;
          this.groupBox1.Text = "Reading";
          // 
          // label1
          // 
          this.label1.AutoSize = true;
          this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.label1.Location = new System.Drawing.Point(669, 19);
          this.label1.Name = "label1";
          this.label1.Size = new System.Drawing.Size(53, 20);
          this.label1.TabIndex = 14;
          this.label1.Text = "Index";
          // 
          // groupBox2
          // 
          this.groupBox2.Controls.Add(this.btn_SendHeader);
          this.groupBox2.Controls.Add(this.btn_SendStarPairs);
          this.groupBox2.Controls.Add(this.btn_SendUvectors);
          this.groupBox2.Controls.Add(this.btn_SendStarIDs);
          this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.groupBox2.Location = new System.Drawing.Point(468, 409);
          this.groupBox2.Name = "groupBox2";
          this.groupBox2.Size = new System.Drawing.Size(760, 80);
          this.groupBox2.TabIndex = 22;
          this.groupBox2.TabStop = false;
          this.groupBox2.Text = "Writing";
          // 
          // Manual
          // 
          this.Manual.AutoSize = true;
          this.Manual.Checked = true;
          this.Manual.Location = new System.Drawing.Point(14, 27);
          this.Manual.Name = "Manual";
          this.Manual.Size = new System.Drawing.Size(113, 28);
          this.Manual.TabIndex = 23;
          this.Manual.TabStop = true;
          this.Manual.Text = "MANUAL";
          this.Manual.UseVisualStyleBackColor = true;
          this.Manual.CheckedChanged += new System.EventHandler(this.Manual_CheckedChanged);
          // 
          // groupBox3
          // 
          this.groupBox3.Controls.Add(this.StarTracker);
          this.groupBox3.Controls.Add(this.Manual);
          this.groupBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.groupBox3.Location = new System.Drawing.Point(1000, 289);
          this.groupBox3.Name = "groupBox3";
          this.groupBox3.Size = new System.Drawing.Size(209, 97);
          this.groupBox3.TabIndex = 24;
          this.groupBox3.TabStop = false;
          this.groupBox3.Text = "MODE";
          // 
          // StarTracker
          // 
          this.StarTracker.AutoSize = true;
          this.StarTracker.Location = new System.Drawing.Point(14, 61);
          this.StarTracker.Name = "StarTracker";
          this.StarTracker.Size = new System.Drawing.Size(184, 28);
          this.StarTracker.TabIndex = 24;
          this.StarTracker.Text = "STAR TRACKER";
          this.StarTracker.UseVisualStyleBackColor = true;
          // 
          // Form1
          // 
          this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
          this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
          this.ClientSize = new System.Drawing.Size(1238, 622);
          this.Controls.Add(this.groupBox3);
          this.Controls.Add(this.groupBox2);
          this.Controls.Add(this.groupBox1);
          this.Controls.Add(this.btn_Clear);
          this.Controls.Add(this.btn_CameraConfig);
          this.Controls.Add(this.btn_Receive);
          this.Controls.Add(this.btn_Send);
          this.Controls.Add(this.btn_Prueba);
          this.Controls.Add(this.pictureBox1);
          this.Controls.Add(this.textBox1);
          this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
          this.MaximizeBox = false;
          this.Name = "Form1";
          this.Text = "CUBESAT CONTROL";
          this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
          this.Load += new System.EventHandler(this.Form1_Load);
          ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
          ((System.ComponentModel.ISupportInitialize)(this.Num)).EndInit();
          ((System.ComponentModel.ISupportInitialize)(this.hEADERBindingSource)).EndInit();
          ((System.ComponentModel.ISupportInitialize)(this.hEADERBindingSource1)).EndInit();
          this.groupBox1.ResumeLayout(false);
          this.groupBox1.PerformLayout();
          this.groupBox2.ResumeLayout(false);
          this.groupBox3.ResumeLayout(false);
          this.groupBox3.PerformLayout();
          this.ResumeLayout(false);
          this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button btn_Prueba;
        private System.Windows.Forms.Button btn_Send;
        private System.Windows.Forms.Button btn_Receive;
        private System.Windows.Forms.Button btn_CameraConfig;
        private System.Windows.Forms.Button btn_Clear;
        private System.Windows.Forms.Button btn_ReadHeader;
        private System.Windows.Forms.Button btn_ReadStarPair;
        private System.Windows.Forms.NumericUpDown Num;
        private System.Windows.Forms.BindingSource hEADERBindingSource;
        private System.Windows.Forms.BindingSource hEADERBindingSource1;
        private System.Windows.Forms.Button btn_ReadStarID;
        private System.Windows.Forms.Button btn_ReadUvector;
        private System.Windows.Forms.Button btn_SendHeader;
        private System.Windows.Forms.Button btn_SendStarPairs;
        private System.Windows.Forms.Button btn_SendStarIDs;
        private System.Windows.Forms.Button btn_SendUvectors;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton Manual;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RadioButton StarTracker;
    }
}

