<?php

/**
 * @file
 * Default rule configurations for Catman Invoice Email.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function catman_invoice_email_default_rules_configuration() {

  $rules = array();

  // Add a reaction rule to send invoice e-mail when invoice is generated.
  $rule = rules_reaction_rule();

  $rule->label = t('Send catman invoice notification e-mail (HTML)');
  $rule->active = TRUE;

  $rule
    ->event('catman_invoice_insert')
    ->action('variable_email_mail', array(
      'to' => '[catman-invoice:order:mail]',
      'variable' => 'catman_invoice_email_invoice_[mail_part]',
      'language' => 'default',
    ));

  $rule->weight = 9;

  $rules['catman_invoice_email_invoice_html'] = $rule;

  // Add a reaction rule to send invoice e-mail to administrator when invoice is generated
  $rule = rules_reaction_rule();

  $rule->label = t('Send catman invoice notification e-mail to administrator (HTML)');
  $rule->active = FALSE;

  $rule
    ->event('catman_invoice_insert')
    ->action('variable_email_mail', array(
      'to:select' => 'site:mail',
      'variable' => 'catman_invoice_email_admin_invoice_[mail_part]',
      'language' => 'default',
    ));

  $rules['catman_invoice_email_admin_invoice_html'] = $rule;

  return $rules;
}
