#include "InvoiceGenerator.h"

InvoiceGenerator::InvoiceGenerator()
{
}

void InvoiceGenerator::Generate(Invoice invoice, std::string filepath)
{
    CheckInvoiceType(invoice);
    PopulateXml(invoice);
    
    SaveXmlToSign(filepath);

#ifdef ZATCA_SDK_SIGNER
    SignXMLZatcaSDK(filepath);
#endif // ZATCA_SDK_SIGNER

#ifdef CHILKAT_SIGNER
    SignXMLChilkat(filepath);
#endif // CHILKAT_SIGNER

    // Load back temp_doc
    signedXml.LoadXml(filepath.c_str());
    UpdateLastQR();
    UpdatePIH();
}

std::string InvoiceGenerator::GetPIH()
{
    std::fstream fs;
    fs.open(PIH_TEMP_FILENAME, std::fstream::in);

    std::string pih;
    std::getline(fs, pih);
    fs.close();

    return pih;
}

std::string InvoiceGenerator::GetQR()
{
    return lastXmlQR;
}

std::string InvoiceGenerator::GetString(double val)
{
    std::ostringstream streamObj;
    streamObj << std::fixed;
    streamObj << std::setprecision(2);

    streamObj << val;

    return streamObj.str();
}

void InvoiceGenerator::PopulateXml(Invoice invoice)
{
    InitializeEmptyXml();

    PopulateUBLExt(invoice);

    PopulateBasicInfo(invoice);
    
    PopulateDocumentReferences(invoice);
    
    PopulateSupplierPartyInfo();

    PopulateCustomerPartyInfo(invoice);
    
    PopulateDeliveryDate(invoice);

    PopulatePatmentMeans(invoice);

    PopulateTaxTotal(invoice);
    
    PopulateLegalMonetaryTotal(invoice);

    PopulateInvoiceLines(invoice);
}

void InvoiceGenerator::CheckInvoiceType(Invoice invoice)
{
    if (invoice.Type != InvoiceType::Simplified && invoice.Type != InvoiceType::Standard)
    {
        throw "Not supported InvoiceType";
    }
}

void InvoiceGenerator::InitializeEmptyXml()
{
    xmlToSign.Clear();
    xmlToSign.put_Utf8(true);
    xmlToSign.put_Tag("Invoice");
    xmlToSign.AddAttribute("xmlns", "urn:oasis:names:specification:ubl:schema:xsd:Invoice-2");
    xmlToSign.AddAttribute("xmlns:cac", "urn:oasis:names:specification:ubl:schema:xsd:CommonAggregateComponents-2");
    xmlToSign.AddAttribute("xmlns:cbc", "urn:oasis:names:specification:ubl:schema:xsd:CommonBasicComponents-2");
    xmlToSign.AddAttribute("xmlns:ext", "urn:oasis:names:specification:ubl:schema:xsd:CommonExtensionComponents-2");
}

void InvoiceGenerator::PopulateUBLExt(Invoice invoice)
{
    // this node doesn't contain real signature, only a placeholder for SDK to put actual signature
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionURI", "urn:oasis:names:specification:ubl:dsig:enveloped:xades");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sac", "urn:oasis:names:specification:ubl:schema:xsd:SignatureAggregateComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sbc", "urn:oasis:names:specification:ubl:schema:xsd:SignatureBasicComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sig", "urn:oasis:names:specification:ubl:schema:xsd:CommonSignatureComponents-2");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|cbc:ID", "urn:oasis:names:specification:ubl:signature:1");

    if (invoice.Type == InvoiceType::Simplified)
        xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|sbc:ReferencedSignatureID", "urn:oasis:names:specification:ubl:signature:Invoice");
    else if (invoice.Type == InvoiceType::Standard)
        xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|sbc:ReferencedSignatureID", "urn:oasis:names:specification:ubl:signature:Invoicesadas");
    
#ifdef ZATCA_SDK_SIGNER
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature", true, "xmlns:ds", "http://www.w3.org/2000/09/xmldsig#");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature", true, "Id", "signature");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:CanonicalizationMethod", true, "Algorithm", "http://www.w3.org/2006/12/xml-c14n11");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:SignatureMethod", true, "Algorithm", "http://www.w3.org/2001/04/xmldsig-more#rsa-sha256");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference", true, "Id", "invoiceSignedData");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference", true, "URI", "");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference|ds:Transforms|ds:Transform", true, "Algorithm", "http://www.w3.org/TR/1999/REC-xpath-19991116");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference|ds:Transforms|ds:Transform|ds:XPath", "not(//ancestor-or-self::ext:UBLExtensions)");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference|ds:Transforms|ds:Transform[1]", true, "Algorithm", "http://www.w3.org/TR/1999/REC-xpath-19991116");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference|ds:Transforms|ds:Transform[1]|ds:XPath", "not(//ancestor-or-self::cac:Signature)");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference|ds:Transforms|ds:Transform[2]", true, "Algorithm", "http://www.w3.org/TR/1999/REC-xpath-19991116");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference|ds:Transforms|ds:Transform[2]|ds:XPath", "not(//ancestor-or-self::cac:AdditionalDocumentReference[cbc:ID='QR'])");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference|ds:Transforms|ds:Transform[3]", true, "Algorithm", "http://www.w3.org/2006/12/xml-c14n11");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference|ds:DigestMethod", true, "Algorithm", "http://www.w3.org/2001/04/xmlenc#sha256");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference|ds:DigestValue", "");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference[1]", true, "Type", "http://www.w3.org/2000/09/xmldsig#SignatureProperties");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference[1]", true, "URI", "#xadesSignedProperties");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference[1]|ds:DigestMethod", true, "Algorithm", "http://www.w3.org/2001/04/xmlenc#sha256");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo|ds:Reference[1]|ds:DigestValue", "");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignatureValue", "");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:KeyInfo|ds:X509Data|ds:X509Certificate", "MIIBmzCCAUECCQDQROomkk8YkDAKBggqhkjOPQQDAjBWMQswCQYDVQQGEwJQTDEQMA4GA1UECAwHU2lsZXNpYTERMA8GA1UEBwwIS2F0b3dpY2UxDTALBgNVBAoMBEdBWlQxEzARBgNVBAMMCkNvbW1vbk5hbWUwIBcNMjEwOTA2MTgwOTA1WhgPNDQ4NTEwMTgxODA5MDVaMFYxCzAJBgNVBAYTAlBMMRAwDgYDVQQIDAdTaWxlc2lhMREwDwYDVQQHDAhLYXRvd2ljZTENMAsGA1UECgwER0FaVDETMBEGA1UEAwwKQ29tbW9uTmFtZTBWMBAGByqGSM49AgEGBSuBBAAKA0IABJboxJQD/AlFyPQCWM3S2ekwGnkhKpOnyP+tjsLYFcJfLLTdX+U/uOfQtKAm/KRXI1E9d8DjOOkVFo5Q1ZQE25QwCgYIKoZIzj0EAwIDSAAwRQIhANULHFfKoroAMgdoUQJ/UwjhD3xHgMeAXjgVpZftENoYAiB7WFgx0hLuJTJbLpYCzpzdpWVOXrIr8g4XvtWKl02j1w==");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:Object|xades:QualifyingProperties", true, "xmlns:xades", "http://uri.etsi.org/01903/v1.3.2#");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:Object|xades:QualifyingProperties", true, "Target", "signature");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:Object|xades:QualifyingProperties|xades:SignedProperties", true, "Id", "xadesSignedProperties");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:Object|xades:QualifyingProperties|xades:SignedProperties|xades:SignedSignatureProperties|xades:SigningTime", time_stamp().c_str());
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:Object|xades:QualifyingProperties|xades:SignedProperties|xades:SignedSignatureProperties|xades:SigningCertificate|xades:Cert|xades:CertDigest|ds:DigestMethod", true, "Algorithm", "http://www.w3.org/2001/04/xmlenc#sha256");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:Object|xades:QualifyingProperties|xades:SignedProperties|xades:SignedSignatureProperties|xades:SigningCertificate|xades:Cert|xades:CertDigest|ds:DigestValue", "9ef6c0b90ae609868bb614772e1d5375464ed1a1793ded751feb1e3414980f7c");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:Object|xades:QualifyingProperties|xades:SignedProperties|xades:SignedSignatureProperties|xades:SigningCertificate|xades:Cert|xades:IssuerSerial|ds:X509IssuerName", "CN=CommonName,O=GAZT,L=Katowice,ST=Silesia,C=PL");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:Object|xades:QualifyingProperties|xades:SignedProperties|xades:SignedSignatureProperties|xades:SigningCertificate|xades:Cert|xades:IssuerSerial|ds:X509SerialNumber", "15007377309689649296");
#endif // ZATCA_SDK_SIGNER
}

void InvoiceGenerator::PopulateBasicInfo(Invoice invoice)
{
    xmlToSign.UpdateChildContent("cbc:ProfileID", "reporting:1.0");
    xmlToSign.UpdateChildContent("cbc:ID", std::to_string(invoice.ID).c_str());
    xmlToSign.UpdateChildContent("cbc:UUID", invoice.UUID.c_str());
    xmlToSign.UpdateChildContent("cbc:IssueDate", invoice.IssueDate.c_str());
    xmlToSign.UpdateChildContent("cbc:IssueTime", invoice.IssueTime.c_str());
    
    if (invoice.Type == InvoiceType::Simplified)
        xmlToSign.UpdateAttrAt("cbc:InvoiceTypeCode", true, "name", "0211010");
    else if (invoice.Type == InvoiceType::Standard)
        xmlToSign.UpdateAttrAt("cbc:InvoiceTypeCode", true, "name", "0100000");

    xmlToSign.UpdateChildContent("cbc:InvoiceTypeCode", "388");

    xmlToSign.UpdateChildContent("cbc:DocumentCurrencyCode", "SAR");
    xmlToSign.UpdateChildContent("cbc:TaxCurrencyCode", "SAR");
    xmlToSign.UpdateChildContent("cac:BillingReference|cac:InvoiceDocumentReference|cbc:ID", invoice.BillingReferenceID.c_str());
}

void InvoiceGenerator::PopulateDocumentReferences(Invoice invoice)
{
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference|cbc:ID", "ICV");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference|cbc:UUID", invoice.AdditionalReference1_UUID.c_str());

    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[1]|cbc:ID", "PIH");
    xmlToSign.UpdateAttrAt("cac:AdditionalDocumentReference[1]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", true, "mimeCode", "text/plain");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[1]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", invoice.PIH.c_str());

    // Placeholder for QR code generated using SDK
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[2]|cbc:ID", "QR");
    xmlToSign.UpdateAttrAt("cac:AdditionalDocumentReference[2]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", true, "mimeCode", "text/plain");

    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[2]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", "");

    xmlToSign.UpdateAttrAt("cac:Signature", true, "", "");
    xmlToSign.UpdateChildContent("cac:Signature|cbc:ID", "urn:oasis:names:specification:ubl:signature:Invoice");
    xmlToSign.UpdateChildContent("cac:Signature|cbc:SignatureMethod", "urn:oasis:names:specification:ubl:dsig:enveloped:xades");
}

void InvoiceGenerator::PopulateSupplierPartyInfo()
{
    xmlToSign.UpdateAttrAt("cac:AccountingSupplierParty|cac:Party|cac:PartyIdentification|cbc:ID", true, "schemeID", "CRN");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyIdentification|cbc:ID", "7001459796");

    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:StreetName", "Prince Migrin st");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:BuildingNumber", "7796");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:PlotIdentification", "4451");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CitySubdivisionName", "Labor City");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CityName", "Khobar");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:PostalZone", "34441");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CountrySubentity", "Eastern Province");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cac:Country|cbc:IdentificationCode", "SA");

    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyTaxScheme|cbc:CompanyID", SELLER_VAT_NUMBER);
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyTaxScheme|cac:TaxScheme|cbc:ID", "VAT");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyLegalEntity|cbc:RegistrationName", SELLER_NAME);
}

void InvoiceGenerator::PopulateCustomerPartyInfo(Invoice invoice)
{
    xmlToSign.UpdateAttrAt("cac:AccountingCustomerParty|cac:Party|cac:PartyIdentification|cbc:ID", true, "schemeID", invoice.CustomerParty.SchemeID.c_str());
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PartyIdentification|cbc:ID", invoice.CustomerParty.ID.c_str());

    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:StreetName", invoice.CustomerParty.StreetName.c_str());
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:BuildingNumber", invoice.CustomerParty.BuildingNumber.c_str());
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:PlotIdentification", invoice.CustomerParty.PlotIdentification.c_str());
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CitySubdivisionName", invoice.CustomerParty.CitySubdivisionName.c_str());
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CityName", invoice.CustomerParty.CityName.c_str());
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:PostalZone", invoice.CustomerParty.PostalZone.c_str());
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cbc:CountrySubentity", invoice.CustomerParty.CountrySubentity.c_str());
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PostalAddress|cac:Country|cbc:IdentificationCode", "SA");
    xmlToSign.UpdateChildContent("cac:AccountingCustomerParty|cac:Party|cac:PartyLegalEntity|cbc:RegistrationName", invoice.CustomerParty.RegistrationName.c_str());
}

void InvoiceGenerator::PopulateDeliveryDate(Invoice invoice)
{
    if (invoice.Type == InvoiceType::Standard)
        xmlToSign.UpdateChildContent("cac:Delivery|cbc:ActualDeliveryDate", invoice.DeliveryDate.c_str());
}

void InvoiceGenerator::PopulatePatmentMeans(Invoice invoice)
{
    xmlToSign.UpdateChildContent("cac:PaymentMeans|cbc:PaymentMeansCode", invoice.PaymentMeansCode.c_str());
    xmlToSign.UpdateChildContent("cac:PaymentMeans|cbc:InstructionNote", invoice.InstructionNote.c_str());
}

void InvoiceGenerator::PopulateTaxTotal(Invoice invoice)
{
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cbc:TaxAmount", GetString(invoice.TaxAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxableAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxableAmount", GetString(invoice.TaxableAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxAmount", GetString(invoice.TaxAmount).c_str());
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:ID", "S");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:Percent", GetString(invoice.VATPercent).c_str());
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cac:TaxScheme|cbc:ID", "VAT");

    xmlToSign.UpdateAttrAt("cac:TaxTotal[1]|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal[1]|cbc:TaxAmount", GetString(invoice.TaxAmount).c_str());
}

void InvoiceGenerator::PopulateLegalMonetaryTotal(Invoice invoice)
{
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:LineExtensionAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:LineExtensionAmount", GetString(invoice.LineExtensionAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:TaxExclusiveAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:TaxExclusiveAmount", GetString(invoice.TaxExclusiveAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:TaxInclusiveAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:TaxInclusiveAmount", GetString(invoice.TaxInclusiveAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:PayableAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:PayableAmount", GetString(invoice.PayableAmount).c_str());
}

void InvoiceGenerator::PopulateInvoiceLines(Invoice invoice)
{
    for (int i = 0; i < invoice.InvoiceLines.size(); i++)
    {
        auto invoiceLine = invoice.InvoiceLines[i];

        std::string temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cbc:ID";
        xmlToSign.UpdateChildContent(temp.c_str(), invoiceLine.ID.c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cbc:InvoicedQuantity";
        xmlToSign.UpdateAttrAt(temp.c_str(), true, "", "");
        xmlToSign.UpdateChildContent(temp.c_str(), std::to_string(invoiceLine.Quantity).c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cbc:LineExtensionAmount";
        xmlToSign.UpdateAttrAt(temp.c_str(), true, "currencyID", "SAR");
        xmlToSign.UpdateChildContent(temp.c_str(), GetString(invoiceLine.LineExtensionAmount).c_str());

        xmlToSign.UpdateAttrAt("cac:InvoiceLine|cac:TaxTotal|cbc:TaxAmount", true, "currencyID", "SAR");
        xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:TaxTotal|cbc:TaxAmount", GetString(invoiceLine.TaxAmount).c_str());
        xmlToSign.UpdateAttrAt("cac:InvoiceLine|cac:TaxTotal|cbc:RoundingAmount", true, "currencyID", "SAR");
        xmlToSign.UpdateChildContent("cac:InvoiceLine|cac:TaxTotal|cbc:RoundingAmount", GetString(invoiceLine.RoundingAmount).c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cbc:Name";
        xmlToSign.UpdateChildContent(temp.c_str(), invoiceLine.Name.c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cac:ClassifiedTaxCategory|cbc:ID";
        xmlToSign.UpdateChildContent(temp.c_str(), "S");

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cac:ClassifiedTaxCategory|cbc:Percent";
        xmlToSign.UpdateChildContent(temp.c_str(), GetString(invoice.VATPercent).c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cac:ClassifiedTaxCategory|cac:TaxScheme|cbc:ID";
        xmlToSign.UpdateChildContent(temp.c_str(), "VAT");

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Price|cbc:PriceAmount";
        xmlToSign.UpdateAttrAt(temp.c_str(), true, "currencyID", "SAR");
        xmlToSign.UpdateChildContent(temp.c_str(), GetString(invoiceLine.PriceAmount).c_str());
    }
}

void InvoiceGenerator::InjectQRCode(Invoice invoice)
{
    QRCodeData qr;
    qr.SellersName = QRData("01", SELLER_NAME);
    qr.VATNumber = QRData("02", SELLER_VAT_NUMBER);
    qr.Timestamp = QRData("03", time_stamp().c_str());
    qr.InvoiceTotal = QRData("04", GetString(invoice.LineExtensionAmount).c_str());
    qr.VATTotal = QRData("05", GetString(invoice.TaxAmount).c_str());

    const char* qr_string;

    // TODO: implement QRCode generator if chilkat is used
}

void InvoiceGenerator::SaveXmlToSign(std::string path)
{
    CkStringBuilder sb;
    xmlToSign.GetXmlSb(sb);
    sb.WriteFile(path.c_str(), "utf-8", false);
}

void InvoiceGenerator::SaveSignedXml(std::string path)
{
    CkStringBuilder sb;
    signedXml.GetXmlSb(sb);
    sb.WriteFile(path.c_str(), "utf-8", false);
}

void InvoiceGenerator::SignXMLZatcaSDK(std::string filename)
{
    std::string signCMD = "fatoorah.bat generate -f " + filename + " -x -q";
    system(signCMD.c_str());
}

void InvoiceGenerator::SignXMLChilkat(std::string filename)
{
    XMLSigner signer("gaztCertificate.p12", "123456789");
    
    CkXml xmlToSign;
    if (!xmlToSign.LoadXmlFile(filename.c_str()))
        throw "Failed to load XML file";
    
    signer.SignXML(xmlToSign, filename.c_str());

    //std::string signCMD = "fatoorah.bat generate -f " + filename + " -q";
    //system(signCMD.c_str());
}

void InvoiceGenerator::UpdateLastQR()
{
    int childrenNum = signedXml.get_NumChildren();
    bool qr_found = false;

    for (int i = 0; i < childrenNum; i++)
    {
        CkXml* child = signedXml.GetChild(i);
        
        if (child->FindChild2("cbc:ID"))
        {
            std::string id = child->getChildContent("");
            if (id == "QR")
            {
                child->GetParent2();
                lastXmlQR = child->getChildContent("cac:Attachment|cbc:EmbeddedDocumentBinaryObject");
                qr_found = true;
            }
        }

        delete child;

        if (qr_found)
            break;
    }   
}

void InvoiceGenerator::UpdatePIH()
{
    CkXml* child = signedXml.GetChildWithTag("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|ds:Signature|ds:SignedInfo");
    CkXml* grandChild = child->GetChild(2);
    std::string pih = grandChild->getChildContent("ds:DigestValue");
    
    std::fstream pih_file;
    pih_file.open(PIH_TEMP_FILENAME, std::fstream::out);
    pih_file << pih;
    pih_file.close();
    
    delete grandChild;
    delete child;
}
