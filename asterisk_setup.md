2023-06-30 Setting Up Asterisk
==============================

These are notes on setting up a recent version of Asterisk and trying to get it
to work with the OpenBTS version that is currently being refactored.  Also, a
goal of this setup is to have the OpenBTS Base Station running on a different
node than the Asterisk (e.g. Asterisk on a VM and the base station on a low
power workstation).

These are the VM specs for the Asterisk installation:
 * Running in a VM on ProxMox, which is running on a nice workstation.
 * 2 vCPU
 * 8 GB RAM
 * Debian 11.5.0 (it's what was on the ProxMox box)
 * Asterisk 16.28.0 (The version supplied by the Debian version)

What Do?
--------

Here's what I dood:

 * Install Asterisk:

```shell
apt install asterisk asterisk-dev asterisk-tests
```

 * Add the following to the end of the `cdr_custom.conf` config file:

```
[mappings]
Master.csv => "${CDR(accountcode)}","${CDR(src)}","${CDR(dst)}","${CDR(dcontext)}","${CDR(clid)}","${CDR(channel)}","${CDR(dstchannel)}","","","${CDR(start)}","${CDR(answer)}","${CDR(end)}","${CDR(duration)}","${CDR(billsec)}","${CDR(disposition)}","${CDR(amaflags)}","${CDR(uniqueid)}","${CDR(userfield)}","${CDR(hangupdirection)}","${CDR(bill-context)}","${CDR(bill-rate)}","${CDR(A-Number)}","${CDR(B-Number)}","${CDR(A-IMSI)}","${CDR(B-IMSI)}"
```

 * The entire set of `extentions*` files appears to be in a similar, but
   different format.  Save the old format off to the side and replace with the
   three files from the repository:
   * `extensions.conf`
   * `extensions-range.conf`
   * `extensions-range-test.conf`
   NOTE: Also need to change the 2601 test extension to play the 2600 tone...

 * In the `iax.conf` file, comment out the following sections:
   * `guest`
   * `iaxtel`
   * `iaxfwd`
   This will prevent unauthorized access or access from iaxtel.com.

 * In the `logger.conf` file, make the following changes:
   * Uncomment the `dateformat=%F %T.%3q` line.
   * Comment out the `messages => notice,warning,error` line.
   * Add a new line below the above line: `syslog.local7 => notice,warning,error,verbose`

 * There are a lot of 'noload's for modules in the OpenBTS version of
   `modules.conf`.  For now, I'll leave these out.  They can be added in when
   there's a desire or need to reduce memory footprint or module collision.

 * There are a fair number of differences in the `sip.conf` file.  Clean them up
   and document them later.  For now, merge as necessary.

 * Copy over the `sip-custom-register.conf`.  It only has comments now, but
   looks like it's used to specify authentication information for the BTS for a
   more secure installation.

 * Copy over the `sip-custom-contexts.conf`.  It has information about how the
   base station connects to Asterisk.  Likely will need to add information about
   the base station's IP address here when setting that part up.

 * Change the 'format' line in the `voicemail.conf` file to `format=gsm`.  There
   are more options to look into in this file, but voice is not important right
   now.

 * The following modules failed to load, so placing them in `modules.conf` with
   a 'noload' directive:
   * cel_sqlite3_custom
   * cel_radius
   * cel_tds
   * cdr_pgsql
   * cdr_sqlite3_custom
   * cdr_radius
   * cdr_tds
   * test_http_media_cache
   * chan_unistim
   * pbx_config
   * res_hep_rtcp
   * pbx_dundi
   * res_hep_pjsip
   * res_pjsip_transport_websocket

 * Also adding the following modules as 'noload's in the `modules.conf` file due
   to either being unused or deprecated:
   * cel_pgsql
   * res_config_ldap
   * res_smdi
   * chan_skinny
   * chan_mgcp
   * res_monitor
   * res_adsi
   * app_adsiprog
   * app_nbscat
   * app_url
   * app_getcpeid
   * app_image
   * app_macro
   * app_ices

 * NOTE: 'chan_sip' and `sip.conf` is depricated.  Will need to move the configs
         from this to 'chan_pjsip' and `pjsip.conf`.
   * https://www.asterisk.org/asterisk-21-module-removal-chan_sip/
   * https://wiki.asterisk.org/wiki/display/AST/Configuring+res_pjsip

Packages for Extra Sound Formats
--------------------------------

May look into adding support for other sound formats, depending on protocols
used:

 * asterisk-core-sounds-en-g722/oldstable 1.6.1-1 all
   asterisk PBX sound files - en-us/g722

 * asterisk-core-sounds-en-wav/oldstable 1.6.1-1 all
   asterisk PBX sound files - en-us/wav

 * asterisk-moh-opsound-g722/oldstable 2.03-1.1 all
   asterisk extra sound files - English/g722

 * asterisk-moh-opsound-wav/oldstable 2.03-1.1 all
   asterisk extra sound files - English/wav

 * asterisk-mp3/oldstable-security 1:16.28.0~dfsg-0+deb11u3 amd64
   MP3 playback support for the Asterisk PBX

Packages for Hardware
---------------------

### DAHDI (Digium's Hardware Interfaces)

May look into these later as I'd like to interface this Asterisk to the "POTS":

 * asterisk-dahdi/oldstable-security 1:16.28.0~dfsg-0+deb11u3 amd64
   DAHDI devices support for the Asterisk PBX

 * dahdi/oldstable 1:3.1.0-2 amd64
   utilities for using the DAHDI kernel modules

 * dahdi-dkms/oldstable 1:2.11.1.0.20170917~dfsg-7.4 all
   DAHDI telephony interface (dkms kernel driver)

 * dahdi-linux/oldstable 1:2.11.1.0.20170917~dfsg-7.4 all
   DAHDI telephony interface - Linux userspace parts

 * dahdi-source/oldstable 1:2.11.1.0.20170917~dfsg-7.4 all
   DAHDI telephony interface - source code for kernel driver

### VoiceTronix

This may also be an option:

 * asterisk-vpb/oldstable-security 1:16.28.0~dfsg-0+deb11u3 amd64
   VoiceTronix devices support for the Asterisk PBX

Scratch Pad
-----------


Jun 30 13:39:58 asterisk asterisk[10771]: WARNING[10771]: res_phoneprov.c:1233 in get_defaults: Unable to find a valid server address or name.





