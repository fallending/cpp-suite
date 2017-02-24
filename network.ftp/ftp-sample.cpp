#include "ftplib.h"

int ftp_main(void) {
	ftplib *ftp = new ftplib::ftplib();
	ftp->Connect("ftp.gwdg.de:21");
	ftp->Login("anonymous", "");
	ftp->Dir(NULL, "/ftp/pub");
	ftp->Quit();
	return 0;
}
