#include "Utility.h"

bool VerifyXML(const char* filepath)
{
    CkXml doc;
    bool success = doc.LoadXmlFile(filepath);
    if (success != true) {
        std::cout << "VerifyXML: Failed to load xml file" << "\r\n";
        return false;
    }
    CkStringBuilder sb;
    doc.GetXmlSb(sb);
    
    CkXmlDSig verifier;
    success = verifier.LoadSignatureSb(sb);
    if (success != true) {
        std::cout << verifier.lastErrorText() << "\r\n";
        return false;
    }
    int numSigs = verifier.get_NumSignatures();
    int verifyIdx = 0;
    while (verifyIdx < numSigs) {
        verifier.put_Selector(verifyIdx);
        bool verified = verifier.VerifySignature(true);
        if (verified != true) {
            std::cout << verifier.lastErrorText() << "\r\n";
            return false;
        }
        verifyIdx = verifyIdx + 1;
    }

    std::cout << "All signatures were successfully verified." << "\r\n";

    return true;
}
