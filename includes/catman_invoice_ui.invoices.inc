<?php

/**
 * @file
 * Page callbacks and form builder functions for administering invoices.
 */


/**
 * Form callback: edit the global invoice settings.
 */
function catman_invoice_settings_form($form, &$form_state) {
  $form['catman_invoice_number_method'] = array(
    '#type' => 'radios',
    '#title' => t('Invoice number creation method'),
    '#description' => t('This determines the way invoice numbers are generated.'),
    '#default_value' => variable_get('catman_invoice_number_method', CATMAN_INVOICE_METHOD_YEAR),
    '#options' => array(
      CATMAN_INVOICE_METHOD_INFINITE => t('Infinite (one single number, that is never reset, and incremented at each invoice generation)'),
      CATMAN_INVOICE_METHOD_YEAR => t('Reset every year, with an id incremented at each invoice generation (@invoice_number)', array('@invoice_number' => date('Y').'-[invoice_id]')),
      CATMAN_INVOICE_METHOD_MONTH => t('Reset every month, with an id incremented at each invoice generation (@invoice_number)', array('@invoice_number' => date('Y-m').'-[invoice_id]')),
      CATMAN_INVOICE_METHOD_CALLBACK => t('Invoice number generation is controlled by a callback function that is being passed the invoice object')
    ),

  );

  $callbacks = module_invoke_all('catman_invoice_number_callbacks');
  if ($callbacks) {
    $form['catman_invoice_number_callback'] = array(
      '#type' => 'select',
      '#title' => t('Invoice number creation callback'),
      '#description' => t('This selects the callback function for the callback method.'),
      '#default_value' => variable_get('catman_invoice_number_callback', ''),
      '#options' => $callbacks,
      '#element_validate' => array('catman_invoice_ui_validate_invoice_number_callback'),
      '#states' => array(
        'visible' => array(
          ':input[name="catman_invoice_number_method"]' => array('value' => CATMAN_INVOICE_METHOD_CALLBACK),
        ),
      ),
    );
  }

  return system_settings_form($form);
}

function catman_invoice_ui_validate_invoice_number_callback($element, &$form_state, $form) {
  if ($form_state['values']['catman_invoice_number_method'] == CATMAN_INVOICE_METHOD_CALLBACK) {
    if (empty($form_state['values']['catman_invoice_number_callback'])) {
      form_set_error('catman_invoice_number_callback', t('Please specify a callback function.'));
    }
    elseif (!function_exists($form_state['values']['catman_invoice_number_callback'])) {
      form_set_error('catman_invoice_number_callback', t('"@callback" is not a valid callback function.', array('@callback' => $form_state['values']['catman_invoice_number_callback'])));
    }
  }
}


/**
 * Creates an option for custom callback on commercie_invoice settings page
 *
 */
// function catman_invoice_number_callbacks() {
//   return array('catman_invoice_invoice_gen' => t('Catman invoice number'));
// }

/**
 * Callback for generating a custom invoice number
 * Sets the invoice number by concatenating the date('Y-m') with the order_id
 *
 */
// function catman_invoice_invoice_gen($invoice = NULL) {
//   $order_id = $invoice->order_id;
//   $invoice_prefix = date('Y-m') . '-';
//   return $invoice_prefix . $order_id;
// }

