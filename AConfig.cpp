
#include "AConfig.hpp"
/* ************************************************************************** */
/* ------------------------------     OCCF    ------------------------------- */
/* ************************************************************************** */

AConfig::AConfig(char *file) : error_page(), workerprocess(1), absolute_redirect_on(true), \
default_type("mime-type"), sendfile(false), sendfile_max_chunk(2048 * 1024), send_timeout(60), \
tcp_nopush(false), tcp_nodelay(false), chunked_transfer_encoding(true), \
client_body_buffer_size(16 * 1024), client_header_buffer_size(1024), client_body_timeout(60), \
client_header_timeout(60), client_max_body_size(1024 * 1024), client_body_in_file_only(false), \
client_body_in_single_buffer(false), client_body_temp_path(""), large_client_header_buffers(8 * 1024), \
disable_symlinks(false), keep_alive_disable("msie6"), server_name(""), keep_alive_timeout(000), \
keep_alive_time(000), keep_alive_requests(1000), keep_cache_connection_alive(000), connect_timeout(000), \
read_timeout(000) 
{
    std::string f;

    if (!file)
        f = "./utils/conf.d/default.conf";
    else
        f = static_cast<std::string>(file);

}

AConfig::AConfig(const AConfig& other): error_page(other.error_page), workerprocess(other.workerprocess), \
absolute_redirect_on(other.absolute_redirect_on), default_type(other.default_type), \
sendfile(other.sendfile), sendfile_max_chunk(other.sendfile_max_chunk), send_timeout(other.send_timeout), \
tcp_nopush(other.tcp_nopush), tcp_nodelay(other.tcp_nodelay), chunked_transfer_encoding(true), \
client_body_buffer_size(other.client_body_buffer_size), client_header_buffer_size(other.client_header_buffer_size), \
client_body_timeout(other.client_body_timeout), client_header_timeout(other.client_header_timeout), \
client_max_body_size(other.client_max_body_size), client_body_in_file_only(other.client_body_in_file_only), \
client_body_in_single_buffer(other.client_body_in_single_buffer), client_body_temp_path(other.client_body_temp_path), \
large_client_header_buffers(other.large_client_header_buffers), disable_symlinks(other.disable_symlinks), \
keep_alive_disable(other.keep_alive_disable), server_name(other.server_name), keep_alive_timeout(other.keep_alive_timeout), \
keep_alive_time(other.keep_alive_time), keep_alive_requests(other.keep_alive_requests), \
keep_cache_connection_alive(other.keep_cache_connection_alive), connect_timeout(other.connect_timeout),read_timeout(other.read_timeout)
{
}

AConfig::~AConfig() {}

AConfig& AConfig::operator=(const AConfig& other)
{
    this->error_page = other.error_page;
    this->absolute_redirect_on = (other.absolute_redirect_on);
    this->default_type = (other.default_type);
    this->sendfile = (other.sendfile);
    this->sendfile_max_chunk = (other.sendfile_max_chunk);
    this->send_timeout = (other.send_timeout);
    this->tcp_nopush = (other.tcp_nopush);
    this->tcp_nodelay = (other.tcp_nodelay);
    this->chunked_transfer_encoding = (true);
    this->client_body_buffer_size = (other.client_body_buffer_size);
    this->client_header_buffer_size = (other.client_header_buffer_size);
    this->client_body_timeout = (other.client_body_timeout);
    this->client_header_timeout = (other.client_header_timeout);
    this->client_max_body_size = (other.client_max_body_size);
    this->client_body_in_file_only = (other.client_body_in_file_only);
    this->client_body_in_single_buffer = (other.client_body_in_single_buffer);
    this->client_body_temp_path = (other.client_body_temp_path);
    this->large_client_header_buffers =(other.large_client_header_buffers);
    this->disable_symlinks = (other.disable_symlinks);
    this->keep_alive_disable =(other.keep_alive_disable);
    this->server_name = (other.server_name);
    this->keep_alive_timeout = (other.keep_alive_timeout);
    this->keep_alive_time = (other.keep_alive_time);
    this->keep_alive_requests = (other.keep_alive_requests);
    this->keep_cache_connection_alive = (other.keep_cache_connection_alive);
    this->connect_timeout = (other.connect_timeout);
    this->read_timeout = (other.read_timeout);
    return *this;
}

/* ************************************************************************** */
/* ------------------------------    GETSET   ------------------------------- */
/* ************************************************************************** */
//private

//public

/* ************************************************************************** */
/* ------------------------------    METHOD   ------------------------------- */
/* ************************************************************************** */
