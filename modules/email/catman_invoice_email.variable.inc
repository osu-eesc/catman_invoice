<?php

/**
 * Variable definition
 */

/**
 * Implements hook_variable_info().
 */
function catman_invoice_email_variable_info($options) {

  $variable['catman_invoice_email_invoice_[mail_part]'] = array(
    'title' => t('Invoice Email'),
    'type' => 'mail_html',
    'description' => t('Template for the invoice email sent out to the customer.'),
    'children' => array(
      'catman_invoice_email_invoice_subject' => array(
        'default' => 'Order confirmation: [site:name] order [catman-invoice:order:order-number]',
      ),
      'catman_invoice_email_invoice_body' => array(
        'default' => '<p>Thank you for your [site:name] order.</p><p>Your order number is [catman-invoice:order:order-number], and your order details are shown below. We will notify you when your order ships.</p><p>If this is your first order with us, you will receive a separate e-mail with instructions for logging into your [site:name] account. You can view the status of your order and your order history with us at any time by logging into your [site:name] account at: [site:login-url]</p><p>Please contact us if you have questions. Thank you!</p><p><strong>Extension and Experiment Station Communications</strong><br />Oregon State University<br />422 Kerr Administration Bldg.<br />Corvallis, OR 97331-2119<br />Phone: 541-737-2513 or 800-561-6719<br />Email: puborders@oregonstate.edu</p><br /><h2>Your order details:</h2><div>Invoice number: [catman-invoice:invoice-number]   <br />Order date: [catman-invoice:order:created:short]</div> <br /><table><tr><th style="text-align: left; ">Bill to</th><th style="text-align: left; ">Ship to</th></tr><tr><td>[catman-invoice:order:commerce-customer-billing:commerce_customer_address]<br>[catman-invoice:order:commerce-customer-billing:field_billing_phone]</td><td>[catman-invoice:order:commerce-customer-shipping:commerce_customer_address]<br>[catman-invoice:order:commerce-customer-shipping:field_billing_phone]</td></tr></table><p>[catman-invoice:order:commerce-email-order-items]</p><div class="catman-invoice-footer"><p>Thanks for your order!</p><div><strong>If your invoice shows a balance:</strong><br />If you are paying with an OSU index, we will process a journal voucher to complete your payment.<br />If you are paying with a purchase order, payment is due upon receipt of your order. Please forward this invoice to your accounts payable department. Include the invoice or invoice number with your payment. Make checks payable to OSU and send to:</div><div class="indent-payment">Extension and Experiment Station Communications, Oregon State University, 422 Kerr Administration Bldg., Corvallis, OR 97330-2119</div></div>'
      ),
    ),
    'group' => 'commerce_email',
  );

  $variable['catman_invoice_email_admin_invoice_[mail_part]'] = array(
    'title' => t('Admin Invoice Email'),
    'type' => 'mail_html',
    'description' => t('Template for the invoice email sent out to the administrator.'),
    'children' => array(
      'catman_invoice_email_admin_invoice_subject' => array(
        'default' => 'NOT CURRENTLY USED Customer Invoice [catman-invoice:invoice-number] from [site:name]',
      ),
      'catman_invoice_email_admin_invoice_body' => array(
        'default' => '<p>A customer at [site:name] has just received an invoice.</p><p><strong>Invoice number</strong>: [catman-invoice:invoice-number]</p><p><strong>Customer</strong>: [catman-invoice:order:commerce-customer-billing:commerce_customer_address]</p><p>[catman-invoice:order:commerce-email-order-items]</p><p>You can view the complete invoice at:&nbsp;[site:url]admin/commerce/orders/[catman-invoice:order:order-id]/invoice</p>'
      ),
    ),
    'group' => 'commerce_email',
  );

  return $variable;
}
