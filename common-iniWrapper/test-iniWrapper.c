#include <unistd.h>
#include <stdio.h>

#include <string.h>
#include "ini_wrapper.h"


#define SYSTEM_CONFIG_PATH "/userdata/Demo/systemCfg.ini"

int main(void)
{
    char HardwareVer[16] = {0};
    char SoftwareVer[16] = {0};
	char EquipmentID[32] = {0};
	
	
    if (access(SYSTEM_CONFIG_PATH, F_OK) == -1) {
		ini_write_string(SYSTEM_CONFIG_PATH, "machineInfo", "EquipmentID", "PB-05-00000000000000000000");
    }
	
    ini_write_string(SYSTEM_CONFIG_PATH, "machineInfo", "HardwareVer", "1.0.001");
    ini_write_string(SYSTEM_CONFIG_PATH, "machineInfo", "SoftwareVer", "1.0.022");
    ini_write_string(SYSTEM_CONFIG_PATH, "machineInfo", "ProductionDate", "2021-09-22");  //出厂日期

	printf("====================   Before Read inifile :\n");
	printf("HardwareVer: %s\n", HardwareVer);
	printf("SoftwareVer: %s\n", SoftwareVer);
	printf("EquipmentID: %s\n", EquipmentID);

    ini_read_string(SYSTEM_CONFIG_PATH, "machineInfo", "HardwareVer", HardwareVer,sizeof(HardwareVer));
    ini_read_string(SYSTEM_CONFIG_PATH, "machineInfo", "SoftwareVer", SoftwareVer,sizeof(SoftwareVer));
    ini_read_string(SYSTEM_CONFIG_PATH, "machineInfo", "EquipmentID", EquipmentID,sizeof(EquipmentID));
	
	printf("====================   After Read inifile :\n");
	printf("HardwareVer: %s\n", HardwareVer);
	printf("SoftwareVer: %s\n", SoftwareVer);
	printf("EquipmentID: %s\n", EquipmentID);
	
	
	printf("=============================================================\n");
	return 0;
}
