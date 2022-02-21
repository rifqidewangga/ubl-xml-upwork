#include "Utility.h"

void PopulateSample(CkXml& xmlToSign)
{
    xmlToSign.put_Tag("Invoice");
    xmlToSign.AddAttribute("xmlns", "urn:oasis:names:specification:ubl:schema:xsd:Invoice-2");
    xmlToSign.AddAttribute("xmlns:cac", "urn:oasis:names:specification:ubl:schema:xsd:CommonAggregateComponents-2");
    xmlToSign.AddAttribute("xmlns:cbc", "urn:oasis:names:specification:ubl:schema:xsd:CommonBasicComponents-2");
    xmlToSign.AddAttribute("xmlns:ext", "urn:oasis:names:specification:ubl:schema:xsd:CommonExtensionComponents-2");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionURI", "urn:oasis:names:specification:ubl:dsig:enveloped:xades");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sac", "urn:oasis:names:specification:ubl:schema:xsd:SignatureAggregateComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sbc", "urn:oasis:names:specification:ubl:schema:xsd:SignatureBasicComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sig", "urn:oasis:names:specification:ubl:schema:xsd:CommonSignatureComponents-2");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|cbc:ID", "urn:oasis:names:specification:ubl:signature:1");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|sbc:ReferencedSignatureID", "urn:oasis:names:specification:ubl:signature:Invoice");
    xmlToSign.UpdateChildContent("cbc:ProfileID", "reporting:1.0");
    xmlToSign.UpdateChildContent("cbc:ID", "935");
    xmlToSign.UpdateChildContent("cbc:UUID", "3cf5ee18-ee25-44ea-a444-2c37ba7f28be");
    xmlToSign.UpdateChildContent("cbc:IssueDate", "2021-01-05");
    xmlToSign.UpdateChildContent("cbc:IssueTime", "09:32:40");
    xmlToSign.UpdateAttrAt("cbc:InvoiceTypeCode", true, "name", "0211010");
    xmlToSign.UpdateChildContent("cbc:InvoiceTypeCode", "388");
    xmlToSign.UpdateChildContent("cbc:DocumentCurrencyCode", "SAR");
    xmlToSign.UpdateChildContent("cbc:TaxCurrencyCode", "SAR");
    xmlToSign.UpdateChildContent("cac:BillingReference|cac:InvoiceDocumentReference|cbc:ID", "”Invoice Number: 354; Invoice Issue Date: 2021-02-10”");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference|cbc:ID", "ICV");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference|cbc:UUID", "70");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[1]|cbc:ID", "PIH");
    xmlToSign.UpdateAttrAt("cac:AdditionalDocumentReference[1]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", true, "mimeCode", "text/plain");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[1]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", "NWZlY2ViNjZmZmM4NmYzOGQ5NTI3ODZjNmQ2OTZjNzljMmRiYzIzOWRkNGU5MWI0NjcyOWQ3M2EyN2ZiNTdlOQ==");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[2]|cbc:ID", "QR");
    xmlToSign.UpdateAttrAt("cac:AdditionalDocumentReference[2]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", true, "mimeCode", "text/plain");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[2]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", "AQ1PbWFyIEhvc3BpdGFsAg8zMTAxMjIzOTM1MDAwMDMDFDIwMjEtMDEtMDVUMDk6MzI6NDBaBAYyNTAuMDAFBDAuMDAGLCtuTWtYTUUydFNvdnlrTEtVNlZVbklxODY2N1NNQ29jNkE3dEtjTUtwWTA9B4GwMzA1NjMwMTAwNjA3MmE4NjQ4Y2UzZDAyMDEwNjA1MmI4MTA0MDAwYTAzNDIwMDA0OTZlOGM0OTQwM2ZjMDk0NWM4ZjQwMjU4Y2RkMmQ5ZTkzMDFhNzkyMTJhOTNhN2M4ZmZhZDhlYzJkODE1YzI1ZjJjYjRkZDVmZTUzZmI4ZTdkMGI0YTAyNmZjYTQ1NzIzNTEzZDc3YzBlMzM4ZTkxNTE2OGU1MGQ1OTQwNGRiOTQIIHfALLWTvHti3jFaD8cZAR+Wuh5YLfRsOSgOpN29UPwiCSAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==");
    xmlToSign.UpdateChildContent("cac:Signature|cbc:ID", "urn:oasis:names:specification:ubl:signature:Invoice");
    xmlToSign.UpdateChildContent("cac:Signature|cbc:SignatureMethod", "urn:oasis:names:specification:ubl:dsig:enveloped:xades");
    xmlToSign.UpdateAttrAt("cac:AccountingSupplierParty|cac:Party|cac:PartyIdentification|cbc:ID", true, "schemeID", "CRN");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyIdentification|cbc:ID", "1265126534");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:StreetName", "Kemarat Street,");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:BuildingNumber", "3724");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:PlotIdentification", "9833");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CitySubdivisionName", "Alfalah");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CityName", "Jeddah");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:PostalZone", "15385");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CountrySubentity", "Makkah");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cac:Country|cbc:IdentificationCode", "SA");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyTaxScheme|cbc:CompanyID", "310122393500003");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyTaxScheme|cac:TaxScheme|cbc:ID", "VAT");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyLegalEntity|cbc:RegistrationName", "Omar Hospital");
    xmlToSign.UpdateAttrAt("cac:AccountingCustomerParty|cac:Party|cac:PartyIdentification|cbc:ID", true, "schemeID", "NAT");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PartyIdentification|cbc:ID", "1010101010");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:StreetName", "Kemarat Street,");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:BuildingNumber", "3724");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:PlotIdentification", "9833");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CitySubdivisionName", "Alfalah");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CityName", "Jeddah");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:PostalZone", "15385");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CountrySubentity", "Makkah");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cac:Country|cbc:IdentificationCode", "SA");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PartyLegalEntity|cbc:RegistrationName", "Sara Hamad");
    xmlToSign.UpdateChildContent("cac:Delivery|cbc:ActualDeliveryDate", "2022-02-10");
    xmlToSign.UpdateChildContent("cac:PaymentMeans|cbc:PaymentMeansCode", "42");
    xmlToSign.UpdateChildContent("cac:PaymentMeans|cbc:InstructionNote", "“Returned items”");
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cbc:TaxAmount", "0.00");
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxableAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxableAmount", "0.00");
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxAmount", "0.00");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:ID", "Z");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:Percent", "0");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:TaxExemptionReasonCode", "VATEX-SA-HEA");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:TaxExemptionReason", "Private healthcare to citizen");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cac:TaxScheme|cbc:ID", "VAT");
    xmlToSign.UpdateAttrAt("cac:TaxTotal[1]|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal[1]|cbc:TaxAmount", "0.00");
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:LineExtensionAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:LineExtensionAmount", "250.00");
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:TaxExclusiveAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:TaxExclusiveAmount", "250.00");
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:TaxInclusiveAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:TaxInclusiveAmount", "250.00");
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:PayableAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:PayableAmount", "250.00");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cbc:ID", "18373428");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cbc:InvoicedQuantity", "1");
    xmlToSign.UpdateAttrAt("cac:InvoiceLine|cbc:LineExtensionAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cbc:LineExtensionAmount", "250.00");
    xmlToSign.UpdateAttrAt("cac:InvoiceLine|cac:TaxTotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:TaxTotal|cbc:TaxAmount", "0.00");
    xmlToSign.UpdateAttrAt("cac:InvoiceLine|cac:TaxTotal|cbc:RoundingAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:TaxTotal|cbc:RoundingAmount", "250.00");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:Item|cbc:Name", "Surgery");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:Item|cac:ClassifiedTaxCategory|cbc:ID", "Z");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:Item|cac:ClassifiedTaxCategory|cbc:Percent", "0");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:Item|cac:ClassifiedTaxCategory|cac:TaxScheme|cbc:ID", "VAT");
    xmlToSign.UpdateAttrAt("cac:InvoiceLine|cac:Price|cbc:PriceAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:Price|cbc:PriceAmount", "250.00");
}

void CreatePFX()
{
    //  First load our certificate into a certificate object,
    //  and then get it as a cert chain object.
    CkCert cert;

    bool success = cert.LoadFromFile("../Samples/certs/cert.pem");
    if (success != true) {
        std::cout << cert.lastErrorText() << "\r\n";
        return;
    }

    //  This is the certificate PEM that we loaded:

    //  -----BEGIN CERTIFICATE-----
    //  MIIDozCCAougAwIBAgIJAMRwugDmvniwMA0GCSqGSIb3DQEBCwUAMGgxCzAJBgNV
    //  BAYTAlVTMQswCQYDVQQIDAJJTDEQMA4GA1UEBwwHV2hlYXRvbjEhMB8GA1UECgwY
    //  SW50ZXJuZXQgV2lkZ2l0cyBQdHkgTHRkMRcwFQYDVQQDDA5DaGlsa2F0V2lkZ2V0
    //  czAeFw0xNzA0MTgxMzQxNDVaFw0yMjA0MTcxMzQxNDVaMGgxCzAJBgNVBAYTAlVT
    //  MQswCQYDVQQIDAJJTDEQMA4GA1UEBwwHV2hlYXRvbjEhMB8GA1UECgwYSW50ZXJu
    //  ZXQgV2lkZ2l0cyBQdHkgTHRkMRcwFQYDVQQDDA5DaGlsa2F0V2lkZ2V0czCCASIw
    //  DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMXhMR7TNHSaHgrEGvAmHNqw/8xV
    //  5TcngVO//yHBniDHas5b2zm0AkhY5EW9dn0wTWHivoRZC2soH7/bxRi4uYUaxgve
    //  YLXw6DO2MHSpuTvhSG3+AjsBDa9kXegn9XT1MdPHk9PrHR0sKXGuimkLf4r+Q1oM
    //  iGlhbUyRATwVlmo6AndgniDnj2RFBYV8E8SQ+7SnLPJdXZRDbLNVY/DY6D9stRAY
    //  rHuz/WBlVW7TQVuWwe7Cd9bfFqjqzLwLksKevWvHGteYDGeiCi+uvMMNfp/Br79Y
    //  zJYF/YpTJYE0POBiMwth1FUIYKpZf/O2eUd6RW9h6hocC5QWU9LAq+7kKFMCAwEA
    //  AaNQME4wHQYDVR0OBBYEFKBCsni1BfOyH3dSoY8yL4mDeNbpMB8GA1UdIwQYMBaA
    //  FKBCsni1BfOyH3dSoY8yL4mDeNbpMAwGA1UdEwQFMAMBAf8wDQYJKoZIhvcNAQEL
    //  BQADggEBAF2iV69ma5XegVWpxbc0gui63RE8NjW2dBW0fa4a4fwNH2f8oetZEjw4
    //  kscx7p4ESxyPtDUkLNplAth+D8NNh9IQDWIld+FZrJsis4tkpVcpMsbmB2CW8fL2
    //  IVnVznAN+/PMYEAkeSOnovUGlREHZZu4b9rMVm89+aoCQ9z+byjW9kLKHyvLnUai
    //  uEHp+0EVFP91CRSIcTCXsW1c5yZ8k5bqL0HlauuOO4TA3IegyYM9xBubmcxg8cRO
    //  2F1k+Ge1lu3e+WY+lihaO0p762dF6g/SUMMrFneCPdIhvt4u7Esc9FDxE3xZEq3x
    //  cS5sHTxtTM0LVBi378/x5m1hln5hSJU=
    //  -----END CERTIFICATE-----

    //  Get it as a certificate chain.
    CkCertChain* certChain = cert.GetCertChain();
    if (cert.get_LastMethodSuccess() != true) {
        std::cout << cert.lastErrorText() << "\r\n";
        return;
    }

    //  Next, load the corresponding private key from a PEM.
    CkPrivateKey privKey;
    success = privKey.LoadPemFile("../Samples/certs/privateKey.pem");
    if (success != true) {
        std::cout << privKey.lastErrorText() << "\r\n";
        delete certChain;
        return;
    }

    //  This is the private key PEM:

    //  -----BEGIN RSA PRIVATE KEY-----
    //  MIIEpAIBAAKCAQEAxeExHtM0dJoeCsQa8CYc2rD/zFXlNyeBU7//IcGeIMdqzlvb
    //  ObQCSFjkRb12fTBNYeK+hFkLaygfv9vFGLi5hRrGC95gtfDoM7YwdKm5O+FIbf4C
    //  OwENr2Rd6Cf1dPUx08eT0+sdHSwpca6KaQt/iv5DWgyIaWFtTJEBPBWWajoCd2Ce
    //  IOePZEUFhXwTxJD7tKcs8l1dlENss1Vj8NjoP2y1EBise7P9YGVVbtNBW5bB7sJ3
    //  1t8WqOrMvAuSwp69a8ca15gMZ6IKL668ww1+n8Gvv1jMlgX9ilMlgTQ84GIzC2HU
    //  VQhgqll/87Z5R3pFb2HqGhwLlBZT0sCr7uQoUwIDAQABAoIBAGCP5LWDIWzpLFHa
    //  or6gCqKZjyo6nFFO4Ohqn+jsH+slBTTQVGmTMy302uhBbYnnwUtMJ+ZTwaO3/85T
    //  Q5otwrJ2f0CZcx42AkoB1SGJFVBoPj0WoCYE/JWjZ8P7g+dgI8GR+cyHRjzPKSZF
    //  o1thdgrwyxMtXH/4QCsF89FLQ4xwCJUkj+w0KBkX8isWcBJnKip81MK8rxhgMJ6v
    //  5+DBVvlvm4BRz0hva7HB3TaZgo9ZWZdoSJQ/l33yfIL8H0EJjC6uJ/Bn77JtDzcv
    //  1oUF02Ebu8/Re7RpUqdTIb1GamrOCjuZN66SrCOsh9rRzueU3UTLzjb9FDv8FQDA
    //  5Dm59KECgYEA6zJ2LaiUywth80rAC34jEF85aC3vyKK0MxYELLB9Nw6MNFD1PZly
    //  YkOcI2kxVV+1KqtRYFlfEpCL4flqVnqjVj5jTCCOXqO6RjnPLoupf0yLpj60raO6
    //  Ouw5EDGjfUDBQtkCQNOx0nZLftVy30Ck/V2gVw9sEgWQV0YRavuymKMCgYEA12HB
    //  eHHSo/dK7keiIK7RRQu2ibALXWXsGq9lUbnQAunKRCa3qQtc8OwGRZsdj9u8HwCB
    //  zDu5QIbaQCa1SyDz1CsOysOfTYNhh1SZ4GLiu7/b0v5ktgdtosT9niowo08Y4ZU+
    //  lA8p2eriylznacNOkA8O1g8m1etHqV+cVKUMvJECgYEApoeVO6DosZd+pCfiMIEA
    //  TMBPwl78L6BcXOuSyx2vmwMW7JgB/LqgTck3Ta9Wue9JNEwXE1RUR63HDZpu24p8
    //  Cj2kSyumAoaFBuI5uugyfCrzmiM+BNAvtTa69Kdg7feinzVOLh52AuG1dLmnW0HH
    //  UIoxVFNcHqqH1/OJs6lBfGcCgYEAkQXhn5gEnSMF8SuKnzcW8cbRQiSnglv+fnlb
    //  X4wd49hHuVvYjpp4GkDSeEvZu+PY54cP3tTYB/rFOizWJaAqjdHwQ9c0jJzKLrVo
    //  Zw4uXPzypz9j0K1vxQmfO8Bsv4mi10IGwOr04yalTlz/9NbtL1L0Sm4pWCD0P7eB
    //  K/12dgECgYBXNV5NcLpZhpjo8q05xAiFuwC2e29qYyVwcFVhYdYguutRKImZtjSE
    //  dndNAxa7EDL9NRc5SjX4NHAZoImADRSbgc2rIq2ePY8WORaR+iKsVx7PJGHSiXTL
    //  30X9E3com8ctyTsZTnlJ4Dm7SefkN0NKzqwjxXxZLaUteWBPUt+YAg==
    //  -----END RSA PRIVATE KEY-----

    //  Create a PFX object instance, and add the private key + cert chain.
    CkPfx pfx;
    success = pfx.AddPrivateKey(privKey, *certChain);
    if (success != true) {
        std::cout << pfx.lastErrorText() << "\r\n";
        delete certChain;
        return;
    }

    delete certChain;

    //  Finally, write the PFX w/ a password.
    success = pfx.ToFile("pfxPassword", "../Samples/certs/sample.pfx");
    if (success != true) {
        std::cout << pfx.lastErrorText() << "\r\n";
        return;
    }

    std::cout << "Success." << "\r\n";
}

void WriteXMLToFile(CkXml& doc, const char* path)
{
    CkStringBuilder unsignedXML;
    doc.GetXmlSb(unsignedXML);
    unsignedXML.WriteFile(path, "utf-8", false);
}
