<?php

/**
 * @file
 */
?>
<?php if ($invoice_number): ?>
  <div class="catman-invoice-number container-inline">
    <?php if ($label): ?>
      <div class="prefix">
        <?php print $label; ?></div>
    <?php endif; ?>
    <div>
      <?php print $invoice_number; ?>
    </div>
  </div>
<?php endif; ?>
