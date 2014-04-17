<?php

/**
 * @file
 */
?>
<?php if ($invoice_header): ?>
  <div class="catman-invoice-header">
    <?php if ($label): ?>
      <div class="prefix">
        <?php print $label; ?>
      </div>
    <?php endif; ?>
    <div>
      <?php print $invoice_header; ?>
    </div>
  </div>
<?php endif; ?>


