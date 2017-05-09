<?php

/**
 * @file
 * Order total cost field handler.
 */

/**
 * Field handler: displays the total cost of an order.
 */
class uc_order_handler_field_order_yearly_sales extends uc_order_handler_field_money_amount {

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
    
	//current month and year
    $year  = date('Y-01-01');

    $timestampy = strtotime($year);

    //next year
    $cyear  = date('Y');
      
    //next year
    $nextyear = date('Y', strtotime('+1 year', strtotime($cyear)));

    //convert to timestamp
    $ny = strtotime($nextyear);

    $yearly  = db_query("SELECT SUM(order_total) FROM {uc_orders} WHERE created >= $timestampy AND created <= $ny")->fetchField();

    $result = '<div class="dashLabel">';
    $result .= number_format(floor($yearly)).' MMK';
	$result .= '</div>';

    return $result;
  }

}
