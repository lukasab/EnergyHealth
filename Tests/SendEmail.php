<?php
@extract($_GET);

$to = $_GET["Recipient"];       			//Get recipient of email
$subject = $_GET["Subject"];    			//Get subject of email
$msg = $_GET["Message"];        			//Get message of email

if ($to != "" && $msg != "") {   			//If recipient and message are not empty
  require("class.phpmailer.php");
  $mail = new PHPMailer();
  $mail->isSMTP();
  $mail->Host = "your.smptserver.com";             	//Address of SMTP server
  $mail->Username = 'yourEmail@smptserver.com'; 	//Username of SMPT server
  $mail->Password = 'yourSmptEmailPassword';            //Password of SMPT server
  $mail->SMTPAuth = true;
  $mail->From = 'yourEmail@smptserver.com';     	//Sender of email
  $mail->FromName = "SenderName";                  	//Name of sender
  $mail->AddAddress($to);                      		//Set the recipient
  $mail->isHTML(true);
  $mail->Subject = $subject;                    	//Set subject of email
  $mail->Body = $msg;                          		//Set body of email

  $send = $mail->Send();                       		//Sends email

  if ($send) {						
    echo "Email send";
  } else {
    echo "Erro: ";
  }
}
?>
