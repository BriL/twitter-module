<?php

require 'vendor/autoload.php';
use GuzzleHttp\Client;
use GuzzleHttp\HandlerStack;
use GuzzleHttp\Subscriber\Oauth\Oauth1;
use GuzzleHttp\Exception\RequestException;

/**
* Class used to interact with twitter api
*/

class trfsSocialMedia
{
  /**
  * The tokens, keys and secrets from the app you created at https://dev.twitter.com/apps
  */
  private $config = [
    'base_url' => 'https://api.twitter.com/1.1/'
  ];
  private $name;
  private $screen_name;
  private $description;
  private $friends_count;
  private $followers_count;
  private $favourites_count;
  private $statuses_count;
  private $twitter_feed = array();

  private function set_name($value){
    $this->name = $value;
  }

  public function get_name(){
    return $this->name;
  }

  private function set_screen_name($value){
    $this->screen_name = $value;
  }

  public function get_screen_name(){
    return $this->screen_name;
  }

  private function set_description($value){
    $this->description = $value;
  }

  public function get_description(){
    return $this->description;
  }

  private function set_friends_count($value){
    $this->friends_count = $value;
  }

  public function get_friends_count(){
    return $this->friends_count;
  }

  private function set_followers_count($value){
    $this->followers_count = $value;
  }

  public function get_followers_count(){
    return $this->followers_count;
  }

  private function set_favourites_count($value){
    $this->favourites_count = $value;
  }

  public function get_favourites_count(){
    return $this->favourites_count;
  }

  private function set_statuses_count($value){
    $this->statuses_count = $value;
  }

  public function get_statuses_count(){
    return $this->statuses_count;
  }

  public function get_twitter_feed(){
    return $this->twitter_feed;
  }

  /**
  *  @param  string  $oauth_access_token         OAuth Access Token          ('Access token' on https://apps.twitter.com)
  *  @param  string  $oauth_access_token_secret  OAuth Access Token Secret   ('Access token secret' on https://apps.twitter.com)
  *  @param  string  $consumer_key               Consumer key                ('API key' on https://apps.twitter.com)
  *  @param  string  $consumer_secret            Consumer secret             ('API secret' on https://apps.twitter.com)
  *  @param  string  $user_id                    User id (http://gettwitterid.com/)
  *  @param  string  $screen_name                Twitter handle
  *  @param  string  $count                      The number of tweets to pull out
  */
  public function __construct($oauth_access_token, $oauth_access_token_secret, $consumer_key, $consumer_secret, $user_id, $screen_name, $count = 5)
  {
    $this->config = array_merge($this->config, compact('oauth_access_token', 'oauth_access_token_secret', 'consumer_key', 'consumer_secret', 'user_id', 'screen_name', 'count'));

  }

  /**
   * Goes to the specific url.
   *
   * @param string $url_type
   *   The case which we know which url to use.
   *
   * @return array(response body) || bool
   *   The response data from GET or false if fails.
   */
  public function setUrlAndGo($url_type){
    switch ($url_type) {
      case 'feed':
        $twitter_url = 'statuses/user_timeline.json?user_id=' . $this->config['user_id'] . '&screen_name=' . $this->config['screen_name'] . '&count=' . $this->config['count'];

        $this->define_user_twitter_info($this->get($twitter_url));

        break;
      default:
        watchdog("trfsSocialMedia.class", 'url type not defined', array(), WATCHDOG_ERROR);;
    }
  }

  /**
   * Perform a restful get call.
   *
   * @param string $url
   *   The target URL.
   *
   * @return array(response body) || bool
   *   The response data from GET or false if fails.
   */
  protected function get($url){

    try{

      $stack = HandlerStack::create();

      $middleware = new Oauth1([
        'consumer_key'    => $this->config['consumer_key'],
        'consumer_secret' => $this->config['consumer_secret'],
        'token'           => $this->config['oauth_access_token'],
        'token_secret'    => $this->config['oauth_access_token_secret']
      ]);
      $stack->push($middleware);

      $client = new Client([
        'base_uri' => $this->config['base_url'],
        'handler' => $stack,
        'auth' => 'oauth'
      ]);

      // Now you don't need to add the auth parameter
      $result = $client->get($url);

      if($result->getStatusCode() !== 200){
        Throw new RequestException('Guzzle encountered a ' . $result->getStatusCode() . ' Message: ' . $result->getReasonPhrase());
      }

      return json_decode($result->getBody()->getContents(), true);

    }
    catch (RequestException $e){
      watchdog("trfsSocialMedia.class", '<pre>' . print_r( $e->getMessage(), true) . '</pre>', array(), WATCHDOG_ERROR);
      return false;
    }
  }

   /**
   * Defines the raw feed information and saves it to the class.
   *
   * @param string $raw_feed
   *   The raw json data returned from the twitter api.
   */
  protected function define_user_twitter_info($raw_feeds){
    if($raw_feeds){
      foreach ($raw_feeds as $key => $raw_feed) {
        if($key == 0){
          // retrieve the user data only once
          if(isset($raw_feed['user']['name'])){
            $this->set_name($raw_feed['user']['name']);
          }

          if(isset($raw_feed['user']['screen_name'])){
            $this->set_screen_name($raw_feed['user']['screen_name']);
          }

          if(isset($raw_feed['user']['description'])){
            $this->set_description($this->translate_twitter_text($raw_feed['user']['description']));
          }

          if(isset($raw_feed['user']['friends_count'])){
            $this->set_friends_count($raw_feed['user']['friends_count']);
          }

          if(isset($raw_feed['user']['followers_count'])){
            $this->set_followers_count($raw_feed['user']['followers_count']);
          }

          if(isset($raw_feed['user']['favourites_count'])){
            $this->set_favourites_count($raw_feed['user']['favourites_count']);
          }

          if(isset($raw_feed['user']['statuses_count'])){
            $this->set_statuses_count($raw_feed['user']['statuses_count']);
          }
        }

        if(isset($raw_feed['created_at'])){
          $this->twitter_feed[$raw_feed['id']]['created_at'] = $this->date_difference($raw_feed['created_at']);
        }

        if(isset($raw_feed['text'])){
          $this->twitter_feed[$raw_feed['id']]['text'] = $this->translate_twitter_text($raw_feed['text']);
        }

        if(isset($raw_feed['retweeted_status'])){
          if(isset($raw_feed['retweeted_status']['retweet_count'])){
            $this->twitter_feed[$raw_feed['id']]['retweet_count'] = $raw_feed['retweeted_status']['retweet_count'];
          }

          if(isset($raw_feed['favorite_count'])){
            $this->twitter_feed[$raw_feed['id']]['favorite_count'] = $raw_feed['retweeted_status']['favorite_count'];
          }
        }
        else{
          if(isset($raw_feed['retweet_count'])){
            $this->twitter_feed[$raw_feed['id']]['retweet_count'] = $raw_feed['retweet_count'];
          }

          if(isset($raw_feed['favorite_count'])){
            $this->twitter_feed[$raw_feed['id']]['favorite_count'] = $raw_feed['favorite_count'];
          }
        }
      }
    }
  }

  /**
   * Helper function tat formates the text from twitter.
   *
   * @param string $text
   *   TRaw text sent from twitter.
   * @return sting $formatted_text
   *   Formated text from twitter
   */
  protected function translate_twitter_text($text){

    // translate links
    $formatted_text = preg_replace('/(\b(www\.|https\:\/\/)\S+\b)/', "<a target='_blank' href='$1'>$1</a>", $text);

    // translate links
    $formatted_text = preg_replace('/(\b(www\.|http\:\/\/)\S+\b)/', "<a target='_blank' href='$1'>$1</a>", $formatted_text);

    // translate hashtags
    $formatted_text = preg_replace('/\#(\w+)/', "<a target='_blank' href='https://twitter.com/search?q=$1'>#$1</a>", $formatted_text);

    // translate links
    $formatted_text = preg_replace('/\@(\w+)/', "<a target='_blank' href='http://twitter.com/$1'>@$1</a>", $formatted_text);

    return $formatted_text;
  }

  /**
   * Helper function that formates the date from twitter. Only shows to categories of time
   *
   * @param string $raw_date
   *   Raw date sent from twitter.
   * @return string $time_string
   *   Formated text from twitter
   */
  protected function date_difference($raw_date){
    $datetime1 = new DateTime();
    $datetime2 = date_create($raw_date);
    $time_count = 0;

    $interval = date_diff($datetime1, $datetime2);
    foreach ($interval as $key => $time_interval) {
      if ($key == 'y' || $key == 'm' || $key == 'd' || $key == 'h' || $key == 'i' || $key == 's'){
        switch ($key) {
          case 'y':
            if ($time_interval && $time_count < 2){
              $time_string .= $time_interval . ' years ';
              ++$time_count;
            }
            break;

          case 'm':
            if ($time_interval && $time_count < 2){
              $time_string .= $time_interval . ' mon ';
              ++$time_count;
            }
            break;

          case 'd':
            if ($time_interval && $time_count < 2){
              $time_string .= $time_interval . ' days ';
              ++$time_count;
            }
            break;

          case 'h':
            if ($time_interval && $time_count < 2){
              $time_string .= $time_interval . ' hours ';
              ++$time_count;
            }
            break;
          
          case 'i':
            if ($time_interval && $time_count < 2){
              $time_string .= $time_interval . ' min ';
              ++$time_count;
            }
            break;

          case 's':
            if ($time_interval && $time_count < 2){
              $time_string .= $time_interval . ' sec ';
              ++$time_count;
            }
            break;

          default:
            
            break;
        }
      }
    }

    return $time_string;
    
  }
}
