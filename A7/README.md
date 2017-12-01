Assignment 7. SSH setup and use in applications

Laboratory

When you initially set up your host in the lab, you will be running an operating system, and will be able to connect to the outside world, but you won't be able to connect to the hosts of the other students in the class except in trivial ways. What you'd like to do is to be able to run processes on the other students' hosts. For example, you'd like to be able to log into a neighbor's host, and run a program there that displays on your host.

To do that, you need to set up an account on your neighbor's host, and vice versa so that your neighbor can log into your host and do the same. Unfortunately, the obvious ways to do that involve an initial step that exchanges passwords over the Internet in the clear. We'd like to avoid that.

In this laboratory, the class will divide into teams. Your team will assume that the other teams have all tapped the network connection and can observe the contents of all the packets going back and forth among all your team's computers. Your job is to set up your computers so that you can log into each other's hosts, without letting the other teams into your hosts.

Do not try to actually break into the other team's hosts; this is an exercise in defense, not offense!

Use OpenSSH to establish trusted connections among your teams' hosts. You want to make your logins convenient, so you should use ssh-agent on your host to manage authentication. That is, you should be able to log out of your host (dropping all your connections to the outside world), then log back in, type your passphrase once to ssh-agent, and then be able to use ssh to connect to any of your colleagues' hosts, without typing any passwords or passphrases.

You should also use port forwarding so that you can run a command on a remote host that displays on your host. For example, you should be able to log into a remote host, type the command xterm, and get a shell window on your host.

Keep a log of every step you personally took during the laboratory to configure your or your team members' hosts, and what the results of the step were. The idea behind recording your steps is that you should be able to reproduce your work later, if need be.

Homework

Use GNU Privacy Guard's shell commands to create a key pair. Export the public key, in ASCII format, into a file hw-pubkey.asc. Use this key to create a detached signature for your submission so that the commands described below can successfully verify it.

If you are creating a key pair on the SEASnet GNU/Linux servers, you may exhaust its entropy pool as described in Launchpad bug 706011. The symptom will be a diagnostic saying "It is a good idea to perform some other action (type on the keyboard, move the mouse, utilize the disks) during the prime generation; this gives the random number generator a better chance to gain enough entropy." Since you can't use the keyboard or mouse on the SEASnet servers, you'll have to use the disks, for example, by using the find command to copy every readable file to /dev/null; this is something that you can do in another session that is logged into the same machine. Please remember to interrupt the find once the key pair is generated, so that you don't tie up the server unnecessarily.

Briefly answer the following questions.

Suppose the other teams really had been observing all the bytes going across the network. Is your resulting network still secure? If so, explain why, and explain whether your answer would change if (1) you assumed the other teams had also tapped your keyboards and had observed all of your team's keystrokes, or (2) you are booting off USB and you assume the other teams temporarily had physical control of the USB. If not, explain any weaknesses of your team's setups, focusing on possible attacks by such outside observers.
Explain why the gpg --verify command in the following instructions doesn't really verify that you personally created the tar file in question. How would you go about fixing this problem?
Submit

Submit two files. The first should be a single gzipped tar file hw.tar.gz containing the following files:

The file hw-pubkey.asc as described above.
A copy of your lab log, as a file log.txt.
The answers to the homework, as a file hw.txt. This and log.txt should both be ASCII text files, with with no more than 200 columns per line.
The second file hw.tar.gz.sig should be a detached cleartext signature, in ASCII form, for hw.tar.gz. It should use the key of hw-pubkey.asc.

The following shell commands should work:

gunzip <hw.tar.gz | tar xf -
mkdir -m go-rwx .gnupg
gpg --homedir .gnupg --import hw-pubkey.asc
gpg --verify hw.tar.gz.sig hw.tar.gz
awk '200 < length' log.txt hw.txt
The gpg --verify command should say "Good signature". The last awk command should output nothing.

© 2005, 2007, 2008, 2010, 2012, 2016, 2017 Paul Eggert. See copying rules.
$Id: assign7.html,v 1.28 2017/01/25 00:24:31 eggert Exp $