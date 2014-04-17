<?php

/**
 * @file
 */
?>
<?php if ($balance_due): ?>
  <div class="catman-invoice-balance-due">
    <?php if ($label): ?>
      <div class="prefix">
        <?php print $label; ?>
      </div>
    <?php endif; ?>
    <div>
      <?php print $balance_due; ?>
    </div>
  </div>
<?php endif; ?>


