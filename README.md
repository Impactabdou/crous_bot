# Project Name

Crousifier

## Description

Small personal project. Crousifier is a C coded bot in link with the "trouvermonlogement" API. It hepls you find a "logement" by sending you a and email whenever there is a flat availability.
Make sure to configure your Mailx.

## Configure Postfix to use Gmail’s SMTP as a Relay

#### 1. Install `libsasl2-modules` if not already

```bash
sudo apt-get install libsasl2-modules
```

#### 2. Edit Postfix Config

```bash
sudo nano /etc/postfix/main.cf
```

Add or modify these lines:

```conf
relayhost = [smtp.gmail.com]:587
smtp_use_tls = yes
smtp_sasl_auth_enable = yes
smtp_sasl_security_options = noanonymous
smtp_sasl_password_maps = hash:/etc/postfix/sasl_passwd
smtp_tls_CAfile = /etc/ssl/certs/ca-certificates.crt
```

#### 3. Create Authentication File

```bash
sudo nano /etc/postfix/sasl_passwd
```

Add:

```text
[smtp.gmail.com]:587 yourgmail@gmail.com:your_app_password
```

> ⚠️ **Important**: You must use a **Gmail App Password**, not your Gmail login password.  
> Generate one at: [https://myaccount.google.com/apppasswords](https://myaccount.google.com/apppasswords)

#### 4. Secure and Hash the Password File

```bash
sudo postmap /etc/postfix/sasl_passwd
sudo chown root:root /etc/postfix/sasl_passwd /etc/postfix/sasl_passwd.db
sudo chmod 600 /etc/postfix/sasl_passwd /etc/postfix/sasl_passwd.db
```

#### 5. Restart Postfix

```bash
sudo systemctl restart postfix
```

#### 6. Test Again

```bash
echo "Hello world" | mailx -s "test subject" exemple@deomain.com
```

#### 7. Monitor Logs

```bash
tail -f /var/log/mail.log
```

## Usage
```bash
make        # build
make clean  # clean obj/bin
make docs   # generate Doxygen docs
```
## Run the programme
./bin/crous <city> <mail@domain.com>

## Author
Abderrahmene Kabar Ensicaen

