<?php

/**
 * @file
 * Builds placeholder replacement tokens for invoice-related data.
 */


/**
 * Implements hook_token_info().
 */
function catman_invoice_token_info() {
  $type = array(
    'name' => t('Invoices', array(), array('context' => 'a drupal commerce invoice')),
    'description' => t('Tokens related to individual invoices.'),
    'needs-data' => 'catman-invoice',
  );

  // Tokens for invoices.
  $invoice = array();

  $invoice['invoice-id'] = array(
    'name' => t('Invoice ID', array(), array('context' => 'a drupal commerce invoice')),
    'description' => t('The unique numeric ID of the invoice.'),
  );

  $invoice['invoice-number'] = array(
    'name' => t('Invoice number', array(), array('context' => 'a drupal commerce invoice')),
    'description' => t('The invoice number displayed to the customer.'),
  );

  // Refer to corresponding order from invoice
  $invoice['order'] = array(
    'name' => t('Order'),
    'description' => t('The order associated to the invoice.'),
    'type' => 'commerce-order',
  );

  // Payment information for order
  $invoice['balance-due'] = array(
    'name' => t('Balance due'),
    'description' => t('The order balance due associated to the invoice.'),
    'type' => 'commerce-order',
  );

  // Header block for invoice
  $invoice['invoice-header'] = array(
    'name' => t('Invoice header'),
    'description' => t('Header message for the invoice.'),
    'type' => 'commerce-order',
  );

  return array(
    'types' => array('catman-invoice' => $type),
    'tokens' => array('catman-invoice' => $invoice),
  );
}

/**
 * Implements hook_tokens().
 */
function catman_invoice_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);

  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }

  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'catman-invoice' && !empty($data['catman-invoice'])) {
    $invoice = $data['catman-invoice'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        // Simple key values on the invoice.
        case 'invoice-id':
          $replacements[$original] = $invoice->invoice_id;
          break;

        case 'invoice-number':
          $replacements[$original] = $sanitize ? check_plain($invoice->invoice_number) : $invoice->invoice_number;
          break;

        case 'order':
          if ($invoice->order_id) {
            $order = commerce_order_load($invoice->order_id);
            $replacements[$original] = $sanitize ? check_plain($order->order_number) : $order->order_number;
          }
          break;

        case 'balance-due':
          if ($invoice->balance_due) {
            $order = commerce_order_load($invoice->balance_due);
            $replacements[$original] = $sanitize ? check_plain($invoice->balance_due) : $invoice->balance_due;
          }
          break;

        case 'invoice-header':
          if ($invoice->invoice-header) {
            $order = commerce_order_load($invoice->invoice-header);
            $replacements[$original] = $sanitize ? check_plain($invoice->invoice-header) : $invoice->invoice-header;
          }
          break;
      }
    }

    if ($order_tokens = token_find_with_prefix($tokens, 'order')) {
      $order = commerce_order_load($invoice->order_id);
      $replacements += token_generate('commerce-order', $order_tokens, array('commerce-order' => $order), $options);
    }
  }

  return $replacements;
}
