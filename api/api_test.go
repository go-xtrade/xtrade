package api

import (
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestGetTraderAPI(t *testing.T) {

	uapi := NewTraderAPI("tcp://180.168.146.187:10000", "9999", "<your accout 1>", "your password")
	assert.NotEmpty(t,uapi)
}