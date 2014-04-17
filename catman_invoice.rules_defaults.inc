<?php

/**
 * @file
 * Default rule configurations for Catman Invoice.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function catman_invoice_default_rules_configuration() {

  $rules = array();

  // Add a reaction rule to generate an invoice number
  // when an order is completed
  $rule = rules_reaction_rule();

  $rule->label = t('Generate catman invoice after completing checkout process');
  $rule->active = TRUE;
  $rule->tags = array('catman');
  $rule->weight = 5;

  $rule
    ->event('commerce_checkout_complete')

    ->condition(rules_condition('catman_invoice_exists', array(
      'commerce_order:select' => 'commerce-order'
    ))->negate())
    ->action('catman_invoice_generate', array(
      'commerce_order:select' => 'commerce-order',
    ));

  $rules['catman_invoice_generate'] = $rule;

  // Add a reaction rule to send invoice e-mail when a new commerce invoice is saved.
  $rule = rules_reaction_rule();

  $rule->label = t('Send an catman invoice notification e-mail');
  $rule->active = TRUE;

  $rule
    ->event('catman_invoice_insert')
    ->action('mail', array(
      'to' => '[catman-invoice:order:mail]',
      'subject' => t('Invoice [catman-invoice:invoice-number] at [site:name]'),
      'message' => t("Your order [catman-invoice:order:order-number] is now complete.\n\nYou will be able to find the invoice for your order at:\n\n[site:url]user/[catman-invoice:uid]/invoices/[catman-invoice:invoice-id]\n\nPlease contact us if you have any questions about your invoice."),
      'from' => '',
    ));

  $rules['catman_invoice_email'] = $rule;

  return $rules;
}
