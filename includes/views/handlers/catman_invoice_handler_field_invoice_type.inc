<?php

/**
 * Field handler to translate an invoice type into its readable form.
 */
class catman_invoice_handler_field_invoice_type extends views_handler_field {
  function render($values) {
    $type = $this->get_value($values);
    if ($type) {
      return catman_invoice_type_get_name($type);
    }
  }
}
