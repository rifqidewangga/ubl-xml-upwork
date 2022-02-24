#include "XMLSigner.h"

void XMLSigner::SetupDSigGen()
{
    // Generated using https://tools.chilkat.io/xmlDsigGen.cshtml
    _gen.put_SigLocation("Invoice|ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation");
    _gen.put_SigLocationMod(0);
    _gen.put_SigId("signature");
    _gen.put_SigNamespacePrefix("ds");
    _gen.put_SigNamespaceUri("http://www.w3.org/2000/09/xmldsig#");
    _gen.put_SignedInfoCanonAlg("C14N_11");
    _gen.put_SignedInfoDigestMethod("sha256");

    // Create an Object to be added to the Signature.
    CkXml object1;
    object1.put_Tag("xades:QualifyingProperties");
    object1.AddAttribute("xmlns:xades", "http://uri.etsi.org/01903/v1.3.2#");
    object1.AddAttribute("Target", "signature");
    object1.UpdateAttrAt("xades:SignedProperties", true, "Id", "xadesSignedProperties");
    object1.UpdateChildContent("xades:SignedProperties|xades:SignedSignatureProperties|xades:SigningTime", "TO BE GENERATED BY CHILKAT");
    object1.UpdateAttrAt("xades:SignedProperties|xades:SignedSignatureProperties|xades:SigningCertificate|xades:Cert|xades:CertDigest|ds:DigestMethod", true, "Algorithm", "http://www.w3.org/2001/04/xmlenc#sha256");
    object1.UpdateChildContent("xades:SignedProperties|xades:SignedSignatureProperties|xades:SigningCertificate|xades:Cert|xades:CertDigest|ds:DigestValue", "TO BE GENERATED BY CHILKAT");
    object1.UpdateChildContent("xades:SignedProperties|xades:SignedSignatureProperties|xades:SigningCertificate|xades:Cert|xades:IssuerSerial|ds:X509IssuerName", "TO BE GENERATED BY CHILKAT");
    object1.UpdateChildContent("xades:SignedProperties|xades:SignedSignatureProperties|xades:SigningCertificate|xades:Cert|xades:IssuerSerial|ds:X509SerialNumber", "TO BE GENERATED BY CHILKAT");

    _gen.AddObject("", object1.getXml(), "", "");

    // -------- Reference 1 --------
    _gen.AddSameDocRef("", "sha256", "C14N_11", "", "");
    _gen.SetRefIdAttr("", "invoiceSignedData");

    // -------- Reference 2 --------
    _gen.AddObjectRef("xadesSignedProperties", "sha256", "", "", "http://www.w3.org/2000/09/xmldsig#SignatureProperties");

    _gen.SetX509Cert(_cert, true);

    _gen.put_KeyInfoType("X509Data");
    _gen.put_X509Type("Certificate");

    _gen.put_Behaviors("IndentedSignature,TransformSignatureXPath");
}

bool XMLSigner::LoadCertificate(const char* certPath, const char* certPwd)
{
    bool success = _cert.LoadPfxFile(certPath, certPwd);
    if (success != true) {
        std::cout << _cert.lastErrorText() << "\r\n";
        return false;
    }

    return true;
}

void XMLSigner::SaveSbXml(CkStringBuilder& sb, const char* filepath)
{
    // Saving XML in proper indented format
    CkXml tempXml;
    tempXml.LoadSb(sb, false);
    tempXml.SaveXml(filepath);
}

bool XMLSigner::VerifyXml(CkStringBuilder& sb)
{
    // ----------------------------------------
    // Verify the signatures we just produced...
    CkXmlDSig verifier;
    bool success = verifier.LoadSignatureSb(sb);
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

XMLSigner::XMLSigner(const char* certPath, const char* certPwd)
{
    LoadCertificate(certPath, certPwd);
}

bool XMLSigner::SignXML(CkXml& doc, const char* filepath)
{
    SetupDSigGen();
    
    // Load XML to be signed...
    CkStringBuilder sbXml;
    doc.GetXmlSb(sbXml);

    // Sign the XML...
    bool success = _gen.CreateXmlDSigSb(sbXml);
    if (success != true) {
        std::cout << _gen.lastErrorText() << "\r\n";
        return false;
    }

    // Save the signed XML to a file.
    SaveSbXml(sbXml, filepath);

    VerifyXml(sbXml);

	return true;
}
