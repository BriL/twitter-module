function twitterFeed($){
  var status_left = $('.status-count-left'),
      status_right = $('.status-count-right'),
      left_timeline = $('.twitter-left > .twitter-user-timeline'),
      right_timeline = $('.twitter-right > .twitter-user-timeline');

  $(window).resize(function resize(){
    if ($(this).width() < 768) {
      status_left.addClass('btn btn-blob');
      status_right.addClass('btn btn-blob');
    }
    else{
      status_left.removeClass('btn btn-blob');
      status_right.removeClass('btn btn-blob');      
    }
  }).trigger('resize');

  $('.btn-blob').on('click', function() {
    $(this).toggleClass('blob');
    if ($(this).hasClass('status-count-left')){
      if ($(this).hasClass('blob')){
        left_timeline.show();    
      }
      else{
        left_timeline.hide();
      }
    }
    else if ($(this).hasClass('status-count-right')){
      if ($(this).hasClass('blob')){
        right_timeline.show();
      }
      else{
        right_timeline.hide();
      }
    }
    
  });
}