using System;
using System.Data;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading;
using System.Net.Sockets;
using System.Windows.Forms;
using System.ComponentModel;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.IO;

namespace EmbeddedWebBrowser
{
    public partial class Form1 : Form
    {
        private TcpClient socket = null; // tcp-socket
        private Thread thread = null; // thread to read data from server
        private Mutex mutex = null; // mutex for pausing thread at reading time

        public Form1(string[] args)
        {
            InitializeComponent();
            mutex = new Mutex();
            thread = MakeThread();
            socket = MakeSocket(Convert.ToInt32(args[0]));
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            webBrowser1.Navigate(GetIndexUrl());
        }

        private string GetIndexUrl()
        {
            // loads default index.html
            string currentDir = Directory.GetCurrentDirectory();
            return String.Format("file:///{0}/index.html", currentDir);
        }

        /// <summary>
        /// makes thread
        /// </summary>
        /// <returns></returns>
        private Thread MakeThread()
        {
            Thread thread = new Thread(new ThreadStart(ThreadProc));
            thread.Start();
            return thread;
        }

        /// <summary>
        /// makes socket
        /// </summary>
        /// <param name="port"></param>
        /// <returns></returns>
        private TcpClient MakeSocket(int port)
        {
            TcpClient socket = new TcpClient();
            try
            {
                socket.Connect("127.0.0.1", port);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            return socket;
        }

        /// <summary>
        /// reads socket
        /// </summary>
        /// <returns></returns>
        private string ReadSocket()
        {
            try
            {
                NetworkStream stream = socket.GetStream();
                int size = socket.ReceiveBufferSize;
                byte[] buffer = new byte[size];
                stream.Read(buffer, 0, size);
                return System.Text.Encoding.ASCII.GetString(buffer);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            return "";
        }

        /// <summary>
        /// process executing in thread
        /// </summary>
        private void ThreadProc()
        {
            while (true)
            {
                if (socket != null)
                {
                    if (socket.Connected)
                    {
                        if (socket.Available > 0)
                        {
                            if (mutex.WaitOne())
                            {
                                string data = ReadSocket();
                                if (data.ToLower().StartsWith("http://") 
                                    || data.ToLower().StartsWith("https://"))
                                {
                                    // we have an url to be shown in web browser
                                    webBrowser1.Navigate(data);
                                    Console.WriteLine("webbrowser: web page loaded ok");
                                }
                                else if (data.StartsWith("index.html"))
                                {
                                    // loads de index.html default web page
                                    webBrowser1.Navigate(GetIndexUrl());
                                    Console.WriteLine("webbrowser: index.html loaded ok");
                                }
                                mutex.ReleaseMutex();
                            }
                        }
                    }
                }
            }
        }
    }
}
