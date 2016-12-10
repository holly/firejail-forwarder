# firejail-forwarder

 login shell into firejail sandbox

## install

```
$ sudo gcc -o /usr/bin/firejail-forwarder firejail-forwarder.c
$ sudo setcap CAP_SETUID+ep /usr/bin/firejail-forwarder
# or sudo chmod u+s /usr/bin/firejail-forwarder
```

## make firejail jail

```
$ sudo debootstrap xenial /jail
$ sudo mkdir /jail/root/bin
# download substitute-user.py
$ sudo curl -L -o /jail/root/bin/substitute-user.py https://gist.githubusercontent.com/holly/897381210d62f6321f2ffb15e6d5b463/raw/substitute-user.py
$ sudo chmod +x /jail/root/bin/substitute-user.py
```

## make jail user

```
$ sudo groupadd -g 10000 jailusers
$ sudo useradd -s /usr/bin/firejail-forwarder -d /nonexistent -u 10001 -g 10001 -G 10000 jailuser
$ sudo chroot /jail groupadd -g 10000 jailusers
$ sudo chroot /jail useradd -s /bin/bash -m -d /home/jailuser -u 10001 -g 100001 -G 10000 jailuser
```

## start firejail sandbox

```
$ sudo firejail --name=SANDBOX_NAME  --chroot=/jail
```

## switch user

```
$ sudo su - jailuser
No directory, logging in with HOME=/
account: polly
Switching to pid 7583, the first child process inside the sandbox
changing root to /proc/7583/root
```
