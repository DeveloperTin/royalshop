<?php

/**
 * @file
 * Views handler: Return actions for order id.
 */

/**
 * Returns actions for an order.
 */
class uc_order_handler_field_publisher_report extends views_handler_field {

  /**
   * Overrides views_handler_field::render().
   */
  	function render($values) 
	{
		if(isset($_GET['tid']) && $_GET['tid']!="")
		{
			$tid = $_GET['tid'];
			$total = 0;
	
			//set address with variable
			$address = "<small>No(1243),Wayzayandar Road,between Thitsar Road Parami Road<br> South Okalapa Tsp, 6th Quarter<br>";
			$address.= "Ph:09 786251505,09 264200107,09 265716656<br> Email: customerservice@royalshop.biz<br>http://royalshop.biz</small>";
	
			//publisher id 
			$publishername  = db_query("SELECT name FROM taxonomy_term_data WHERE tid = '$tid'")->fetchField();
			$publisherid    = db_query("SELECT entity_id FROM field_revision_field_book_publisher_name WHERE field_book_publisher_name_tid = '$tid'");

			$result = '<input type="button" onclick="printDiv(\'printableArea\')" value="Print" />';
			$result.= '<div id="printableArea" >';
			$result.= '<div style="clear:both;border-bottom:3px solid red;min-height:140px;"><img src="sites/all/themes/royalShopTheme/logo.png" style="float:left"><span style="text-align:right;float:right;">'.$address.'</span></div><br>';
			$result.= '<h2 style="text-align:center;color:#000;font-family:Unicode">'.$publishername.'</h2><p style="text-align:right">'.date('M-Y').'<p>';
			$result.= '<table class="publisherTable" style="border-collapse:collapse;">';
			$result.= '<tr>';
			$result.= '<td style="border:1px solid #000;padding:6px;width:50%">စာအုပ်အမည်</td>';
			$result.= '<td style="border:1px solid #000;padding:6px;">ယခင်လ<br>လက်ကျန်</td>';
			$result.= '<td style="border:1px solid #000;padding:6px;">ယခုလ<br>အရောင်း</td>';
			$result.= '<td style="border:1px solid #000;padding:6px;">ယခုလ<br>လက်ကျန်</td>';
			$result.= '<td style="border:1px solid #000;padding:6px;">စျေးနှုန်း</td>';
			$result.= '<td style="border:1px solid #000;padding:6px;">သင့်ငွေ</td>';
			$result.= '</tr>';

			foreach ($publisherid as $key => $publisher) 
			{
				$nid = $publisher->entity_id;
	
				$books  = db_query("SELECT title,cost,price FROM uc_order_products WHERE nid='$nid'")->fetchField();
				$cost   = db_query("SELECT cost FROM uc_order_products WHERE nid='$nid'")->fetchField();
				$qty    = db_query("SELECT SUM(qty) FROM uc_order_products WHERE nid='$nid'")->fetchField();
				$stock  = db_query("SELECT stock FROM uc_product_stock WHERE nid='$nid'")->fetchField();
	
				if(!empty($books))
				{
					$result.= '<tr>';
					$result.= '<td class="bookDesc" style="border:1px solid #000;padding:6px;">'.$books.'</td>';
					$result.= '<td class="lastMonthQty" style="border:1px solid #000;padding:6px;">'.$qty.'</td>';
					$result.= '<td class="thisMonthQty" style="border:1px solid #000;padding:6px;">'.$stock.'</td>';
					$result.= '<td class="lastStockQty" style="border:1px solid #000;padding:6px;">'.($qty+$stock).'</td>';
					$result.= '<td class="eachPrice" style="border:1px solid #000;padding:6px;">'.number_format($cost).'MMK</td>';
					$result.= '<td class="totalPrice" style="border:1px solid #000;padding:6px;">'.number_format($stock*$cost).'MMK</td>';
					$result.= '</tr>';
				}
	
				$total += ($qty*$cost);
			}
	
			$result.= '<tr><td colspan="4" style="border:1px solid #000;padding:6px;"></td><td style="border:1px solid #000;padding:4px;">Total</td><td style="border:1px solid #000;padding:4px;">'.number_format($total).'MMK</td></tr>';
			$result.= '<tr>';
			$result.= '<td colspan="3" style="text-align:left"><br> <u>Royal Shop ကိုယ်စား(ငွေပေးပို့သူ)</u></td>';
			$result.= '<td colspan="3" style="text-align:left"><br><u>'.$publishername.' ကိုယ်စား(ငွေလက်ခံသူ)</u></td>';
			$result.= '</tr>';
			$result.= '<tr>';
			$result.= '<td colspan="3" style="text-align:left"> အမည်<br><br>မှတ်ပုံတင်</td>';
			$result.= '<td colspan="3" style="text-align:left"> အမည်<br><br>မှတ်ပုံတင်</td>';
			$result.= '</tr>';
			$result.= '</table></div>';
	
			return $result;
	
		}else
		{
			$publisherlists = db_query("SELECT tid,name FROM {taxonomy_term_data} WHERE vid='29'");
	
			$result = '<table class="publisherReportTable">';
			  
			foreach ($publisherlists as $key => $publisher) 
			{
				$name = $publisher->name;
				$tid  = $publisher->tid;
	
				$result.= '<tr>';
				$result.= '<td><a href="publisherReport?tid='.$tid.'">'.$name.'</a></td>';
				$result.= '</tr>';
			}
	
			$result.= '</table>';
	
			return $result;
		}  
	}
  /**
   * Overrides views_handler_field::query().
   */
  function query() {
    // Do nothing.
  }

}
