var twitterFeedInit = ($) => {
  var status_left = $('.status-count-left'),
      status_right = $('.status-count-right'),
      left_timeline = $('.twitter-left > .twitter-user-timeline'),
      right_timeline = $('.twitter-right > .twitter-user-timeline')

  $('.btn-blob').on('click', function(){
    $(this).toggleClass('blob')
    if ($(this).hasClass('status-count-left')){
      if ($(this).hasClass('blob')){
        left_timeline.show()    
      }
      else{
        left_timeline.hide()
      }
    }
    else if ($(this).hasClass('status-count-right')){
      if ($(this).hasClass('blob')){
        right_timeline.show()
      }
      else{
        right_timeline.hide()
      }
    }
    
  })
}