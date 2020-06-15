#include <string.h>

void unrar_test(const char* rarFilePath, const char* dstPath)
{
	HANDLE hArcData; //Archive Handle
	struct RAROpenArchiveDataEx rarOpenArchiveData;
    struct RARHeaderDataEx rarHeaderData;
    memset(&rarOpenArchiveData, 0, sizeof(rarOpenArchiveData));
    memset(&rarHeaderData, 0, sizeof(rarHeaderData));

    rarOpenArchiveData.ArcName = (char*) rarFilePath;
    rarOpenArchiveData.CmtBuf = NULL;
    rarOpenArchiveData.CmtBufSize = 0;
    rarOpenArchiveData.OpenMode = RAR_OM_EXTRACT;
    hArcData = RAROpenArchiveEx(&rarOpenArchiveData);
    
    LOG("UnRAR [%s]", rarFilePath);
     
    if (rarOpenArchiveData.OpenResult != ERAR_SUCCESS)   
    {   
        LOG("OpenArchive '%s' Failed!", rarOpenArchiveData.ArcName);
        return;   
    }   
      
    while (RARReadHeaderEx(hArcData, &rarHeaderData) == ERAR_SUCCESS)   
    {   
        LOG("Extracting '%s' (%d) ...", rarHeaderData.FileName, rarHeaderData.UnpSize + (((uint64_t)rarHeaderData.UnpSizeHigh) << 32));   
    
        if (RARProcessFile(hArcData, RAR_EXTRACT, dstPath, NULL) != ERAR_SUCCESS)   
        {   
            LOG("ERROR: UnRAR Extract Failed!");
            return;
        }   
    }   

    RARCloseArchive(hArcData);   
}

