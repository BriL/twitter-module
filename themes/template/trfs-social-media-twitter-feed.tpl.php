<div class="trfs-twitter-container">
  <div class="twitter-large-container">
    <div class="twitter-large parallax-window" data-parallax="scroll" data-image-src="<?php print file_create_url('public://twitter_wallpaper.jpg'); ?>" data-bleed="90"  data-speed="0.3"></div>
  </div>
  <div class="trfs-container container">
    <div class="row">
      <?php foreach ($twitter_feeds as $key => $twitter_feed): ?>
        <div class="col-sm-6 <?php ($key == 'twitter_left') ? print 'twitter-right' : print 'twitter-left' ?>">
          <div class="twitter-user-info">
            <div class="twitter-user-name">
              <h2><?php print $twitter_feed->get_name(); ?></h2>
              <span><a target='_blank' href='http://twitter.com/<?php print $twitter_feed->get_screen_name(); ?>'>@<?php print $twitter_feed->get_screen_name(); ?></a></span>
            </div>
            <div class="twitter-user-description">
              <span><?php print $twitter_feed->get_description(); ?></span>
            </div>
            <div class="row twitter-user-statuses">
              <div class="col-xs-3 twitter-user-tweet">
                <div class="twitter-label">Tweets</div>
                <div class="twitter-status btn btn-blob status-count<?php ($key == 'twitter_left') ? print '-right' : print '-left' ?>">
                  <span><?php print $twitter_feed->get_statuses_count(); ?></span>
                </div>
              </div>
              <div class="col-xs-3 twitter-user-tweet">
                <div class="twitter-label">Following</div>
                <div class="twitter-status">
                  <span><?php print $twitter_feed->get_friends_count(); ?></span>
                </div>
              </div>
              <div class="col-xs-3 twitter-user-tweet">
                <div class="twitter-label">Followers</div>
                <div class="twitter-status">
                  <span><?php print $twitter_feed->get_followers_count(); ?></span>
                </div>
              </div>
              <div class="col-xs-3 twitter-user-tweet">
                <div class="twitter-label">Likes</div>
                <div class="twitter-status">
                  <span><?php print $twitter_feed->get_favourites_count(); ?></span>
                </div>
              </div>
            </div>
          </div>
          <div class="twitter-user-timeline">
            <?php foreach ($twitter_feed->get_twitter_feed() as $key => $tweet):?>
             <div id="slide" class="fullwidth-slider" ></div>
              <div class="row twitter-tweet">
                <div class="col-xs-12 twitter-created-at">
                  <p><a target='_blank' href='http://twitter.com/<?php print $twitter_feed->get_screen_name(); ?>'>@<?php print $twitter_feed->get_screen_name(); ?></a>&nbsp<?php print $tweet['created_at']; ?></p>
                </div>
                <div class="col-xs-12">
                  <p><?php print $tweet['text']; ?></p>
                </div>
                <div class="col-xs-4 twitter-icon">
                  <a href="https://twitter.com/intent/tweet?in_reply_to=<?php print $key; ?>" target="_blank"><i class="fa fa-reply" aria-hidden="true"></i></a>
                </div>
                <div class="col-xs-4 twitter-icon">
                  <p><a href="https://twitter.com/intent/retweet?tweet_id=<?php print $key; ?>" target="_blank"><i class="fa fa-retweet" aria-hidden="true"></i>&nbsp<?php print $tweet['retweet_count']; ?></a></p>
                </div>
                <div class="col-xs-4 twitter-icon">
                  <p><a href="https://twitter.com/intent/like?tweet_id=<?php print $key; ?>" target="_blank"><i class="fa fa-heart" aria-hidden="true"></i>&nbsp<?php print $tweet['favorite_count']; ?></a></p>
                </div>
              </div>
            <?php endforeach; ?>
          </div>
        </div>
      <?php endforeach; ?>
    </div>
  </div>
</div>