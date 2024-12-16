using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using System.IO.Ports;

namespace labs_CI
{
    public partial class Form1 : Form
    {
        SerialPort port = null;
        bool start_code = false;
        Thread threads;
        string data_rx = "";
        public Form1()
        {
            InitializeComponent();
            refresh_com();
        }
        private void newthread()
        {
            //creating new thread to be able to get data continuesly
            threads = new Thread(recive_data);
            //making the thread mode is STA
            threads.SetApartmentState(ApartmentState.STA);
            //starting thread
            threads.Start();
        }
        private void recive_data()
        {
            //string recived_data = "";
            while (true)
            {
                try
                {
                    //byte[] arr = new byte[1024];
                    // for (int i = 0; i < 1024; i++)
                    // {
                    //     arr[i] = (byte)port.ReadByte();
                    // }
                    //converting Byte array into string
                    //  recived_data = Encoding.ASCII.GetString(arr);
                    Invoke((MethodInvoker)delegate
                    {
                        Verify.Text = data_rx;
                    });
                    
                }
                catch (Exception e)
                {
                    MessageBox.Show("Error Couldn't Recive Data Dute to: " + e, "Error !!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                Thread.Sleep(100);
            }
           
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }
        private void button1_Click(object sender, EventArgs e)
        {
            connect();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            disconnect();
        }
        private void button3_Click(object sender, EventArgs e)
        {
            refresh_com();
        }

        private void refresh_com()
        {
            comboBox1.DataSource = SerialPort.GetPortNames();
        }
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            disconnect();
        }
        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void connect()
        {
                port = new SerialPort(comboBox1.SelectedItem.ToString());
                port.DataReceived += new SerialDataReceivedEventHandler(data_rx_handler);
                port.BaudRate = 9600;
                port.DataBits = 8;
                port.StopBits = StopBits.One;
            try
            {
                if (!port.IsOpen)
                {
                    port.Open();
                    label1.Text = "Connected";
                    label1.ForeColor = Color.Green;
                    newthread();
                }
            }
            catch (Exception ex) { MessageBox.Show("Error Couldn't open port Dute to: " + ex, "Error !!", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }
        private void disconnect()
        {
            try
            {
                if (port.IsOpen)
                {
                    port.Close();
                    label1.Text = "Disconnected";
                    label1.ForeColor = Color.Red;
                }
            }
            catch (Exception ex) { }
        }
        private void send()
        {
            try
            {
                port.Write(textBox1.Text);
            }
            catch (Exception ex) { }
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                send();
            }
        }
        private void data_rx_handler(object sender, SerialDataReceivedEventArgs e)
        {
            port = (SerialPort)sender;
            String Recived_Data = port.ReadExisting();
            if (start_code)
            {
                Recived_Data = Recived_Data.Replace("|", "");
                Recived_Data = Recived_Data.Replace("$", "");
                data_rx += Recived_Data;
            }
            if (Recived_Data.Contains("|"))
            {
                data_rx += "";
                start_code = true;
            }
            else if (Recived_Data.Contains("$"))
            {
                start_code = false;
            }
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            // textBox2.Text = data_rx;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            string mode = comboBox2.SelectedItem.ToString();
            switch (mode)
            {
                case ("Sin"):
                    port.Write("i" + textBox1.Text + textBox3.Text );
                    break;
                case ("Square"):
                    port.Write("q" + textBox1.Text + textBox3.Text );
                    break;
                case ("Staircase"):
                    port.Write("t" + textBox1.Text + textBox3.Text);
                    break;
                case ("Triangular"):
                    port.Write("r" + textBox1.Text + textBox3.Text);
                    break;
            }

        }
    }
}
