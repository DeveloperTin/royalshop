<?php

/**
 * @file
 * Order total cost field handler.
 */

/**
 * Field handler: displays the total cost of an order.
 */
class uc_order_handler_field_order_monthly_qty extends uc_order_handler_field_money_amount {

  /**
   * Constructor.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['order_id'] = 'order_id';
  }

  /**
   * Overrides views_handler_field::query().
   */
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
    // Do nothing else with the query, we'll be retrieving the information directly.
  }

  /**
   * Overrides views_handler_field::render().
   */
  function render($values) {
	  
    $month = date('Y-M-01');

    $timestampm = strtotime($month);

    $cmonth = date('M');

    $nextmonth = date('Y-M', strtotime('+1 month', strtotime($cmonth)));
    $nextmonth = $nextmonth."-01";

    $nm = strtotime($nextmonth);
    
	$sql  = db_query("SELECT order_id,created FROM uc_orders WHERE created >= $timestampm AND created <= $nm");
	
	$count = 0;
	
	foreach ($sql as $row) {
			$order_id = $row->order_id;

			$sql = db_query("SELECT qty FROM uc_order_products WHERE order_id=$order_id");
			foreach ($sql as $row2) {
				$qty = (int)$row2->qty;
	    		$count += $qty;
			}	
		}
		
	$result = '<div class="dashLabel">';
    $result .= $count.' pcs';
	$result .= '</div>';

    return $result;
  }
}

