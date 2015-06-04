void SendEMail(String TextToSend)
{
byte smtpip[] = { 999, 999, 999, 999 }; // SMTP server IP
if (client.connect(smtpip,25))
 {
 client.println("EHLO XXX"); // XXX - your SMTP server name
 client.println("AUTH LOGIN");                    // see "<a href="http://base64-encoder-online.waraxe.us/" rel="nofollow">http://base64-encoder-online.waraxe.us/</a>"
 client.println("XXXXXXXXXXXXXXXXXXXXXXX");       // Type mail box name and encode it
 client.println("XXXXXXXXXXXX");                  // Type password and encode it
 client.println("MAIL FROM:<admin@XXX.XXX>");  
 client.println("RCPT TO:<admin@XXX.XXX>");
 client.println("DATA");
 client.println("from:admin@XXX.XXX");
 client.println("to:XXX@XXX.XXX.XX");
 client.print("SUBJECT: ");
 client.println(TextToSend); // subject
 client.println();
 client.println(TextToSend); // body
 client.println(".");
 client.println(".");
 client.println("QUIT");
 delay(1000);
 client.stop();
 }
else { Serial.println("SMTP connection ERROR..."); }
}
