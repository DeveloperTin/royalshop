<?php

/**
 * @file
 * Order total cost field handler.
 */

/**
 * Field handler: displays the total cost of an order.
 */
class uc_order_monthly_sales_amount extends uc_order_handler_field_money_amount {

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
    $month = date('Y-M-01');

    $timestampm = strtotime($month);
    $timestampy = strtotime($year);

    //next year
    $cyear  = date('Y');
    $cmonth = date('M');
      
    //next year
    $nextyear = date('Y', strtotime('+1 year', strtotime($cyear)));

    //next mont
    $nextmonth = date('Y-M', strtotime('+1 month', strtotime($cmonth)));
    $nextmonth = $nextmonth."-01";


    //convert to timestamp
    $ny = strtotime($nextyear);
    $nm = strtotime($nextmonth);

    $monthly = db_query("SELECT SUM(order_total) FROM {uc_orders} WHERE created >= $timestampm AND created <= $nm")->fetchField();
    $yearly  = db_query("SELECT SUM(order_total) FROM {uc_orders} WHERE created >= $timestampy AND created <= $ny")->fetchField();

    $morder  = db_query("SELECT SUM(qty) FROM {uc_order_products}")->fetchField();
    
    $sql3 = db_query("SELECT order_id,created FROM uc_orders");

    $count3 = 0;
    foreach ($sql3 as $row) {
      $order_id = $row->order_id;
      //echo $order_id;

      $sql = db_query("SELECT qty FROM uc_order_products WHERE order_id=$order_id");
      foreach ($sql as $row2) {
        $qty = (int)$row2->qty;
          $count3 += $qty;
      }
      
    }

    //create table layout
    $result  = '<table>';
    $result .= '<tr>';
    $result .= '<td>Monthly Total Amount:</td>';
    $result .= '<td>'.number_format(floor($monthly)).' MMK</td>';
    $result .= '</tr>';
    $result .= '<tr>';
    $result .= '<td>Yearly Total Amount:</td>';
    $result .= '<td>'.number_format(floor($yearly)).' MMK</td>';
    $result .= '</tr>';
    $result .= '<tr>';
    $result .= '<td>Monthly Ordered Books:</td>';
    $result .= '<td>'.$morder.' qty</td>';
    $result .= '</tr>';
    $result .= '<tr>';
    $result .= '<td>Yearly Ordered Books:</td>';
    $result .= '<td>'.$count3.'</td>';
    $result .= '</tr>';

    return $result;
    //return $nextmonth;
    
  }

}
