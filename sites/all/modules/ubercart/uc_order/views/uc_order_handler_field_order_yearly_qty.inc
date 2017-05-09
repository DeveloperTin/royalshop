<?php

/**
 * @file
 * Order total cost field handler.
 */

/**
 * Field handler: displays the total cost of an order.
 */
class uc_order_handler_field_order_yearly_qty extends uc_order_handler_field_money_amount {

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
    
	    $year  = date('Y-01-01');
	    
		$timestampy = strtotime($year);

	    //next year
	    $cyear  = date('Y');
	      
	    //next year
	    $nextyear = date('Y', strtotime('+1 year', strtotime($cyear)));


	    //convert to timestamp
	    $ny = strtotime($nextyear);
    
	$sql2 = db_query("SELECT order_id,created FROM uc_orders WHERE created >= $timestampy AND created <= $ny");
	
	$count = 0;
	
	foreach ($sql2 as $row) {
			$order_id = $row->order_id;
			//echo $order_id;

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
