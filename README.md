# Todo List
Original source code: https://github.com/abimaelmartell/todo

## Compile
```sh
./configure
make
```

## Deploy
```
heroku create --stack cedar --buildpack http://github.com/heroku/heroku-buildpack-c.git
git push heroku master
```

## Tests

### Integration
Integration tests are written entirely in ruby, using the rspec gem and the httparty gem to do http requests.

To run the integration tests you need tu run the app `./todo` then run `rspec` in another shell.
