#include "InvoiceGenerator.h"

InvoiceGenerator::InvoiceGenerator(const char* certPath, const char* certPwd) : xmlSigner(certPath, certPwd)
{
}

void InvoiceGenerator::Generate(Invoice invoice, std::string filepath)
{
    PopulateXml(invoice);
    WriteXMLToFile("../Samples/unsignedDoc.xml");
    xmlSigner.SignXML(xmlToSign, filepath.c_str());
}

void InvoiceGenerator::PopulateXml(Invoice invoice)
{
    xmlToSign.Clear();

    xmlToSign.put_Tag("Invoice");
    xmlToSign.AddAttribute("xmlns", "urn:oasis:names:specification:ubl:schema:xsd:Invoice-2");
    xmlToSign.AddAttribute("xmlns:cac", "urn:oasis:names:specification:ubl:schema:xsd:CommonAggregateComponents-2");
    xmlToSign.AddAttribute("xmlns:cbc", "urn:oasis:names:specification:ubl:schema:xsd:CommonBasicComponents-2");
    xmlToSign.AddAttribute("xmlns:ext", "urn:oasis:names:specification:ubl:schema:xsd:CommonExtensionComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions", true, "Id", "UBLExtensions");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionURI", "urn:oasis:names:specification:ubl:dsig:enveloped:xades");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sac", "urn:oasis:names:specification:ubl:schema:xsd:SignatureAggregateComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sbc", "urn:oasis:names:specification:ubl:schema:xsd:SignatureBasicComponents-2");
    xmlToSign.UpdateAttrAt("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures", true, "xmlns:sig", "urn:oasis:names:specification:ubl:schema:xsd:CommonSignatureComponents-2");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|cbc:ID", "urn:oasis:names:specification:ubl:signature:1");
    xmlToSign.UpdateChildContent("ext:UBLExtensions|ext:UBLExtension|ext:ExtensionContent|sig:UBLDocumentSignatures|sac:SignatureInformation|sbc:ReferencedSignatureID", "urn:oasis:names:specification:ubl:signature:Invoice");
    xmlToSign.UpdateChildContent("cbc:ProfileID", "reporting:1.0");
    xmlToSign.UpdateChildContent("cbc:ID", std::to_string(invoice.ID).c_str());
    xmlToSign.UpdateChildContent("cbc:UUID", invoice.UUID.c_str());
    xmlToSign.UpdateChildContent("cbc:IssueDate", invoice.IssueDate.c_str());
    xmlToSign.UpdateChildContent("cbc:IssueTime", invoice.IssueTime.c_str());
    xmlToSign.UpdateAttrAt("cbc:InvoiceTypeCode", true, "name", "010100");
    xmlToSign.UpdateChildContent("cbc:InvoiceTypeCode", "380");
    xmlToSign.UpdateChildContent("cbc:DocumentCurrencyCode", "SAR");
    xmlToSign.UpdateChildContent("cbc:TaxCurrencyCode", "SAR");
    
    xmlToSign.UpdateChildContent("cac:BillingReference|cac:InvoiceDocumentReference|cbc:ID", invoice.BillingReferenceID.c_str());
    
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference|cbc:ID", "ICV");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference|cbc:UUID", invoice.AdditionalReference1_UUID.c_str());
    
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[1]|cbc:ID", "PIH");
    xmlToSign.UpdateAttrAt("cac:AdditionalDocumentReference[1]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", true, "mimeCode", "text/plain");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[1]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", invoice.PIH.c_str());
    
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[2]|cbc:ID", "QR");
    xmlToSign.UpdateAttrAt("cac:AdditionalDocumentReference[2]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", true, "mimeCode", "text/plain");
    xmlToSign.UpdateChildContent("cac:AdditionalDocumentReference[2]|cac:Attachment|cbc:EmbeddedDocumentBinaryObject", invoice.QRCode.c_str());
    
    xmlToSign.UpdateAttrAt("cac:Signature", true, "", "");
    xmlToSign.UpdateChildContent("cac:Signature|cbc:ID", "urn:oasis:names:specification:ubl:signature:Invoice");
    xmlToSign.UpdateChildContent("cac:Signature|cbc:SignatureMethod", "urn:oasis:names:specification:ubl:dsig:enveloped:xades");
    
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:StreetName", "Some street name");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:cbc:BuildingNumber", "111");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:PlotIdentification", "asdzxc");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CityName", "AlKhobar, Labor City");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:PostalZone", "zone");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CountrySubentity", "subentity");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cbc:CitySubdivisionName", "subdiv");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PostalAddress|cac:Country|cbc:IdentificationCode", "SA");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyTaxScheme|cbc:CompanyID", "ILCACAO");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyTaxScheme|cac:TaxScheme", "VAT");
    xmlToSign.UpdateChildContent("cac:AccountingSupplierParty|cac:Party|cac:PartyLegalEntity|cbc:RegistrationName", "ILCACAO");
    
    xmlToSign.UpdateChildContent("cac:PaymentMeans|cbc:InstructionNote", invoice.InstructionNote.c_str());

    xmlToSign.UpdateAttrAt("cac:TaxTotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cbc:TaxAmount", std::to_string(invoice.TaxAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxableAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxableAmount", std::to_string(invoice.TaxableAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cbc:TaxAmount", std::to_string(invoice.TaxAmount).c_str());
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:ID", "Z");
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cbc:Percent", std::to_string(invoice.VATPercent).c_str());
    xmlToSign.UpdateChildContent("cac:TaxTotal|cac:TaxSubtotal|cac:TaxCategory|cac:TaxScheme|cbc:ID", "VAT");
    
    xmlToSign.UpdateAttrAt("cac:TaxTotal[1]|cbc:TaxAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:TaxTotal[1]|cbc:TaxAmount", std::to_string(invoice.TaxAmount).c_str());
    
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:LineExtensionAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:LineExtensionAmount", std::to_string(invoice.LineExtensionAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:TaxExclusiveAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:TaxExclusiveAmount", std::to_string(invoice.TaxExclusiveAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:TaxInclusiveAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:TaxInclusiveAmount", std::to_string(invoice.TaxInclusiveAmount).c_str());
    xmlToSign.UpdateAttrAt("cac:LegalMonetaryTotal|cbc:PayableAmount", true, "currencyID", "SAR");
    xmlToSign.UpdateChildContent("cac:LegalMonetaryTotal|cbc:PayableAmount", std::to_string(invoice.PayableAmount).c_str());

    for (int i = 0; i < invoice.InvoiceLines.size(); i++)
    {
        auto invoiceLine = invoice.InvoiceLines[i];

        std::string temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cbc:ID";
        xmlToSign.UpdateChildContent(temp.c_str(), invoiceLine.ID.c_str());
        
        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cbc:InvoicedQuantity";
        xmlToSign.UpdateAttrAt(temp.c_str(), true, "unitCode", "PCE");
        xmlToSign.UpdateChildContent(temp.c_str(), std::to_string(invoiceLine.Quantity).c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cbc:LineExtensionAmount";
        xmlToSign.UpdateAttrAt(temp.c_str(), true, "currencyID", "SAR");
        xmlToSign.UpdateChildContent(temp.c_str(), std::to_string(invoiceLine.LineExtensionAmount).c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cbc:Name";
        xmlToSign.UpdateChildContent(temp.c_str(), invoiceLine.Name.c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cac:ClassifiedTaxCategory|cbc:ID";
        xmlToSign.UpdateChildContent(temp.c_str(), "Z");

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cac:ClassifiedTaxCategory|cbc:Percent";
        xmlToSign.UpdateChildContent(temp.c_str(), std::to_string(invoice.VATPercent).c_str());

        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Item|cac:ClassifiedTaxCategory|cac:TaxScheme|cbc:ID";
        xmlToSign.UpdateChildContent(temp.c_str(), "VAT");
        
        temp = "cac:InvoiceLine[" + std::to_string(i) + "]|cac:Price|cbc:PriceAmount";
        xmlToSign.UpdateAttrAt(temp.c_str(), true, "currencyID", "SAR");
        xmlToSign.UpdateChildContent(temp.c_str(), std::to_string(invoiceLine.PriceAmount).c_str());
    }
}

void InvoiceGenerator::WriteXMLToFile(std::string path)
{
    CkStringBuilder unsignedXML;
    xmlToSign.GetXmlSb(unsignedXML);
    unsignedXML.WriteFile(path.c_str(), "utf-8", false);
}

