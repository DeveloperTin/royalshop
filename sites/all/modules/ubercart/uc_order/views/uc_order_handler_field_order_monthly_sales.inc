<?php

/**
 * @file
 * Order total cost field handler.
 */

/**
 * Field handler: displays the total cost of an order.
 */
class uc_order_handler_field_order_monthly_sales extends uc_order_handler_field_money_amount {

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
    
	//current month
    $month = date('Y-M-01');

    $timestampm = strtotime($month);
    $cmonth = date('M');

    //next mont
    $nextmonth = date('Y-M', strtotime('+1 month', strtotime($cmonth)));
    $nextmonth = $nextmonth."-01";

    $nm = strtotime($nextmonth);

    $monthly = db_query("SELECT SUM(order_total) FROM {uc_orders} WHERE created >= $timestampm AND created <= $nm")->fetchField();

	$result = '<div class="dashLabel">';
    $result .= number_format(floor($monthly)).' MMK';
	$result .= '</div>';

    return $result;
  }

}
