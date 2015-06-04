01
	void SendEMail(String TextToSend)
02
	{
03
	byte smtpip[] = { 999, 999, 999, 999 }; // SMTP server IP
04
	if (client.connect(smtpip,25))
05
	 {
06
	 client.println("EHLO XXX"); // XXX - your SMTP server name
07
	 client.println("AUTH LOGIN");                    // see "<a href="http://base64-encoder-online.waraxe.us/" rel="nofollow">http://base64-encoder-online.waraxe.us/</a>"
08
	 client.println("XXXXXXXXXXXXXXXXXXXXXXX");       // Type mail box name and encode it
09
	 client.println("XXXXXXXXXXXX");                  // Type password and encode it
10
	 client.println("MAIL FROM:<admin@XXX.XXX>");  
11
	 client.println("RCPT TO:<admin@XXX.XXX>");
12
	 client.println("DATA");
13
	 client.println("from:admin@XXX.XXX");
14
	 client.println("to:XXX@XXX.XXX.XX");
15
	 client.print("SUBJECT: ");
16
	 client.println(TextToSend); // subject
17
	 client.println();
18
	 client.println(TextToSend); // body
19
	 client.println(".");
20
	 client.println(".");
21
	 client.println("QUIT");
22
	 delay(1000);
23
	 client.stop();
24
	 }
25
	else { Serial.println("SMTP connection ERROR..."); }
26
	}
