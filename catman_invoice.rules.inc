<?php

/**
 * @file
 * Rules integration for invoices.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_condition_info()
 */
function catman_invoice_rules_condition_info() {
  $items = array();
  $items['catman_invoice_exists'] = array(
    'label' => t('Catman invoice exists for order'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order to check'),
      ),
    ),
    'group' => t('Catman Invoice'),
    'callbacks' => array(
      'execute' => 'catman_invoice_rules_condition_exists'
    )
  );
  return $items;
}

function catman_invoice_rules_condition_exists($order) {
  $order_id = $order->order_id;
  $query = new EntityFieldQuery();
  $results = $query
    ->entityCondition('entity_type', 'catman_invoice')
    ->propertyCondition('order_id', $order_id, '=')
    ->execute();
  if (isset($results['catman_invoice'])) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Implements hook_rules_action_info().
 */
function catman_invoice_rules_action_info() {
  $actions = array();

  $actions['catman_invoice_generate'] = array(
    'label' => t('Generate catman invoice'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order to update'),
      ),
    ),
    'group' => t('Catman Invoice'),
    'callbacks' => array(
      'execute' => 'catman_invoice_rules_generate',
    ),
  );

  return $actions;
}

function catman_invoice_rules_generate($order) {
  $invoice = catman_invoice_new($order->uid, $order->order_id);
  catman_invoice_save($invoice);
}


