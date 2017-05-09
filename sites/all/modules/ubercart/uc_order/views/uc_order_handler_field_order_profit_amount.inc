<?php

/**
 * @file
 * Order total cost field handler.
 */

/**
 * Field handler: displays the total cost of an order.
 */
class uc_order_handler_field_order_profit_amount extends uc_order_handler_field_money_amount {

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

  		//get all books from order lists
    	$orders = db_query("SELECT order_id FROM {uc_orders}");
		$baseurl = 'http://localhost:8888/royalshop/node/';

    	foreach ($orders as $order) {
    		//get order_id 
      		$order_id = $order->order_id;

      		//distinct book from all orders
        	$books = db_query("SELECT DISTINCT(nid),model,title,cost,price FROM {uc_order_products}");
    
        	//set table layout for view
	        $result = '<table class="table">';
	        $result.= '<tr>';
	        //$result.= '<td>ID</td>';
			$result.= '<td>SKU No.</td>';
	        $result.= '<td>Book Name</td>';
	        $result.= '<td>Qty</td>';
	        $result.= '<td>Price</td>';
	        $result.= '<td>Cost</td>';
	        $result.= '<td>Profit</td>';
	        $result.= '<tr>';

	        foreach ($books as $book) {          	
	          	$nid   = $book->nid;
				$model = $book->model;
	          	$title = $book->title;
	          	$cost  = $book->cost;
	          	$price = $book->price;

	          	//sum qty for each book
	          	$qty = db_query("SELECT SUM(qty) FROM {uc_order_products} WHERE nid=$nid")->fetchField();

	          	$result.= '<tr>';
	          	//$result.= '<td>'.$nid.'</td>';
				$result.= '<td><a href="'.$baseurl.$nid.'">'.$model.'</td>';
	          	$result.= '<td><a href="'.$baseurl.$nid.'">'.$title.'</a></td>';
	          	$result.= '<td>'.$qty.'</td>';
	          	$result.= '<td>'.number_format(floor($price)).' MMK</td>';
	          	$result.= '<td>'.number_format(floor($cost)).' MMK</td>';
	          	$result.= '<td>'.number_format($qty*$price - $qty*$cost).' MMK</td>';
	          	$result.= '<tr>';
	        }
    	}
    	return $result;
  	}
}

