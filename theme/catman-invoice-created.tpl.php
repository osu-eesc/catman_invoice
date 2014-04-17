<?php

/**
 * @file
 */
?>
<?php if ($created): ?>
  <div class="catman-invoice-created container-inline">
    <?php if ($label): ?>
      <div class="prefix">
        <?php print $label; ?>
      </div>
    <?php endif; ?>
    <div>
      <?php print $created; ?>
    </div>
  </div>
<?php endif; ?>


