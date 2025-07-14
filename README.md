# Virtual Protocol Adapter & Multiware Framework (mwfw2)

[![License](https://img.shields.io/badge/License-All%20Rights%20Reserved-red.svg)](LICENSE)
[![Version](https://img.shields.io/badge/Version-5.5.10.2-blue.svg)](CHANGELOG)
[![C++](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)](https://isocpp.org/)

A comprehensive C++ framework providing Virtual Protocol Adapter (VPA) RPC
services and multiware system capabilities for distributed computing
environments.

[![CMake on a single platform](https://github.com/ichibrosan/fw/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/ichibrosan/fw/actions/workflows/cmake-single-platform.yml)

## Overview

The Virtual Protocol Adapter & Multiware Framework (mwfw2) is a
sophisticated, C++ framework designed for distributed computing
environments. It provides a robust foundation for building applications
with RPC capabilities, user management, and both command-line and
browser-based interfaces.

## System Architecture

The Virtual Protocol Adapter is a light-weight data multiplexing system.
It has both command-line and web-based interfaces.

When an adapter component is invoked, a shared memory region is established
and initialized. The shared memory can then be accessed either by command-line
utilities, or by browsing its web component CGI scripts.

Each component, command-line or web-based CGI script, instantiates the
MultiWare FrameWork. It is the framework's constructor that creates or accesses
the shared memory region.

### Web-based access to the Virtual Protocol Adapter

Accessing the VPA using a browser is easily accomplished by opening the
following URL:

    http://vpahost/~doug/fw/cgi-bin/index.cgi

This brings up a dialogue box requesting a user name and password.
Entry of these fields results in transfer to the login.cgi which
authenticates the user and subsequently displays the user's dashboard,
consisting of some status information and a few navigation buttons.

The framework consists of two primary, interconnected components:

### 1. Virtual Protocol Adapter (VPA) - Core RPC Infrastructure

The VPA component forms the backbone of the distributed communication system,
providing advanced authentication and security layers, comprehensive RPC
protocol operations, and enterprise network architecture. It implements a
sophisticated 4-stage authentication workflow including Pre-Shared Key (PSK)
validation for initial secure handshake, dynamic token generation and exchange
for session establishment, user credential verification with comprehensive
lookup operations, and authorization level assignment and session handle
creation. The system utilizes industry-standard encryption for all data
transmission, implements secure session tracking with automatic timeout and
cleanup, and provides a granular permission system with configurable
authorization levels.

The RPC protocol operations include VPARPC_FUNC_GET_AUTH for initial
authentication handshake with PSK validation, VPARPC_FUNC_VERSION for server
capability negotiation and version compatibility checking, VPARPC_FUNC_LOOKUP
for user credential verification with database integration, and
VPARPC_FUNC_CREDS for complete user profile retrieval including metadata and
session information. The enterprise network architecture supports scalable
server deployment with multiple deployment options including standalone TCP
servers, system service integration with full inetd/xinetd compatibility for
on-demand service activation, load balancing support with built-in support for
high-availability deployments, and protocol flexibility with configurable
service endpoints and communication protocols.

### 2. Multiware Framework (mwfw2) - System Integration Platform

The mwfw2 component provides comprehensive system utilities and integration
capabilities through its professional user interface system, comprehensive
system integration, and advanced utility components. The professional user
interface system includes advanced console management with sophisticated
text-based interface system using Unicode box-drawing characters, dynamic window
rendering with real-time window sizing, content management, and professional
styling, multi-window support with concurrent window management and layered
display capabilities, and customizable aesthetics with full control over visual
appearance including borders, colors, and formatting.

The comprehensive system integration features environment auto-detection with
intelligent detection of CGI vs. console execution environments, thread-safe
operations with complete shared memory management and mutex protection,
configuration management with multi-source configuration system supporting INI
files, environment variables, and runtime parameters, and logging infrastructure
with enterprise-grade logging supporting multiple output destinations and
severity levels. The advanced utility components include a data processing suite
with CSV parsing, hex dump utilities, and structured data manipulation, security
components with password management, credential validation, and secure data
handling, database integration with schema compilation, query processing, and
transaction management, and development tools with debugging utilities,
performance monitoring, and diagnostic capabilities.

## Technical Features

### Database Integration & Management

The framework provides sophisticated database interaction capabilities through
its schema management system with automated schema compilation, dynamic database
schema processing and validation, query builder with advanced SQL query
construction and parameter binding, transaction management with full ACID
compliance and rollback and commit functionality, data mapping with automatic
conversion between C++ objects and database records, and connection pooling with
efficient database connection management and resource optimization.

The data processing pipeline includes CSV import/export with robust CSV file
processing including error handling and validation, binary data handling with
hex dump utilities for debugging and data analysis, structured data validation
with comprehensive input validation and sanitization, and format conversion with
multi-format data conversion and transformation utilities.

### Web Services & API Integration

The framework extends beyond traditional RPC to provide comprehensive web
service capabilities through its CGI web interface with dynamic HTML generation,
real-time HTML content creation with templating support, session management with
web-based session tracking and secure cookie handling, form processing with
complete form data validation and processing, and response generation with
structured HTTP response generation and proper headers.

The RESTful API framework includes endpoint management with dynamic API endpoint
creation and routing, JSON processing with native JSON parsing and generation
capabilities, authentication integration with seamless integration with VPA
authentication system, and error handling with comprehensive error response
generation and logging.

### Security Architecture & Implementation

The multi-layer security model implements an authentication pipeline with
four-stage authentication process and multiple validation points, session
security with time-based session tokens and automatic expiration and renewal,
data encryption with end-to-end encryption for all sensitive data transmission,
audit trail with complete logging of all authentication and authorization
events, and input validation with comprehensive validation of all user inputs
and system parameters.

Threat protection includes injection prevention with protection against SQL
injection and code injection attacks, session hijacking protection with secure
session token generation and validation, brute force protection with rate
limiting and account lockout mechanisms, and data leakage prevention with secure
error handling that prevents information disclosure.

## Advanced Features & Capabilities

### Enterprise Deployment Options

Standalone server deployment provides independent process architecture with
self-contained server processes and complete resource management, configuration
management with comprehensive configuration system and hot-reload capabilities,
process monitoring with built-in health checking and automatic restart
mechanisms, and resource optimization with memory and CPU usage optimization for
high-performance environments.

System service integration offers init system compatibility with full support
for systemd, SysV init, and other init systems, service discovery with automatic
service registration and discovery mechanisms, load balancing with built-in load
balancing and failover capabilities, and monitoring integration with native
integration with system monitoring tools.

Containerized deployment includes Docker support with complete containerization
support and optimized Docker images, Kubernetes integration with native
Kubernetes deployment and service mesh support, microservices architecture
designed for microservices deployment patterns, and scaling capabilities with
horizontal and vertical scaling support.

### Development & Debugging Tools

The comprehensive debugging suite provides real-time monitoring with live system
monitoring and performance metrics, diagnostic tools with built-in diagnostic
utilities for troubleshooting, performance profiling with CPU and memory
profiling and detailed analysis, and error tracking with advanced error tracking
and reporting capabilities.

The testing framework includes unit testing with built-in unit testing framework
and assertion libraries, integration testing with complete integration testing
capabilities, load testing with performance testing tools for scalability
validation, and mock services with service mocking capabilities for development
and testing.

## Performance & Scalability

### Performance Characteristics

The system is optimized for high throughput with optimization for high-volume
transaction processing, low latency with minimized response times through
efficient architecture, memory efficiency with optimized memory usage and
automatic garbage collection, and CPU optimization with multi-threaded
processing and CPU affinity support.

### Scalability Features

Horizontal scaling provides support for distributed deployments across multiple
servers, vertical scaling offers efficient resource utilization for
single-server deployments, load distribution implements intelligent load
distribution algorithms, and resource management provides dynamic resource
allocation and optimization.

## Integration Capabilities

### External System Integration

The framework supports database systems with native support for PostgreSQL,
MySQL, SQLite, and other databases, message queues with integration with
RabbitMQ, Apache Kafka, and other messaging systems, web servers with native
integration with Apache, Nginx, and other web servers, and monitoring systems
with integration with Prometheus, Grafana, and other monitoring tools.

### API & Protocol Support

Protocol support includes HTTP/HTTPS with complete HTTP protocol support and
SSL/TLS encryption, WebSocket with real-time communication support through
WebSocket protocol, gRPC with high-performance RPC communication and Protocol
Buffers, and custom protocols with framework for implementing custom
communication protocols.

## Project Structure

```
fw/
├── include/              # Comprehensive header files and API definitions
│   ├── CVpaRpc.h        # VPA RPC client class definitions
│   ├── mwfw2.h          # Main framework header
│   ├── vparpc.h         # VPA RPC protocol definitions
│   ├── window.h         # Window management classes
│   └── semigraphics.h   # Console graphics utilities
├── bin/                 # Compiled executables and binaries
│   ├── vparpc_client    # VPA RPC client application
│   ├── vparpc_server    # VPA RPC server daemon
│   └── utilities/       # Additional utility programs
├── lib/                 # Static libraries and shared objects
├── doc/                 # Comprehensive documentation
│   ├── api/            # API reference documentation
│   ├── examples/       # Usage examples and tutorials
│   └── deployment/     # Deployment guides and configurations
├── html/               # Web interface components
│   ├── templates/      # HTML templates
│   ├── static/         # CSS, JavaScript, and image files
│   └── cgi/           # CGI interface files
├── scripts/            # Build, deployment, and maintenance scripts
│   ├── build/         # Build automation scripts
│   ├── deploy/        # Deployment automation
│   └── maintenance/   # System maintenance utilities
├── cgi-bin/           # CGI applications and web services
├── schemas/           # Database schemas and migration scripts
├── config/            # Configuration files and templates
├── tests/             # Test suites and testing utilities
├── retired/           # Legacy code and deprecated components
├── log/               # Log files and debugging output
└── tmp/               # Temporary files and build artifacts
```

## Build System & Dependencies

### Build Requirements

The system requires a C++ compiler that is C++20 compatible (GCC 10+, Clang 10+,
MSVC 2019+), build system with CMake 3.15 or higher using modern CMake
practices, operating system support for Linux (Ubuntu 20.04+, CentOS 8+, RHEL
8+), macOS 10.15+, Windows 10+, network libraries with TCP/IP stack and socket
support, and threading with POSIX threads (pthreads) or Windows threading
support.

### Optional Dependencies

Optional dependencies include database support with PostgreSQL, MySQL, SQLite
development libraries, web server support with Apache HTTPD, Nginx with
development headers, monitoring with Prometheus client libraries and system
monitoring tools, and testing with Google Test, Catch2, or similar testing
frameworks.

### Build Process

```shell script
# Complete build with all features
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_ALL_FEATURES=ON ..
make -j$(nproc)
sudo make install

# Development build with debugging
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTING=ON ..
make -j$(nproc)
make test
```

## Configuration Management System

### Multi-Source Configuration

The framework supports sophisticated configuration management through INI
configuration files, environment variable integration, and runtime configuration
options. The primary configuration file supports server configuration with
hostname, port, max_connections, timeout, SSL settings including ssl_enabled,
ssl_cert, ssl_key, security configuration with psk_key, session_timeout,
max_login_attempts, lockout_duration, require_strong_passwords, logging
configuration with level, output, file_path, max_file_size, max_files,
debug_mode, database configuration with host, port, database, username,
password, pool_size, connection_timeout, and monitoring configuration with
enabled, metrics_port, health_check_interval, performance_monitoring.

### Environment Variable Integration

Environment-specific configuration supports VPA_SERVER_HOST, VPA_SERVICE_NAME,
VPA_LOG_LEVEL, VPA_PSK_KEY, VPA_DB_PASSWORD, and VPA_MONITORING_ENABLED for
flexible deployment configuration.

## Network Services & Protocol Implementation

### VPA RPC Protocol Specifications

The protocol message structure includes a header of 16 bytes containing
version (4 bytes), size (4 bytes), function (4 bytes), and reserved (4 bytes),
followed by a variable-length payload. Supported RPC functions include
VPARPC_FUNC_GET_AUTH (0x0001) for initial authentication with PSK validation,
VPARPC_FUNC_VERSION (0x0002) for server version and capability negotiation,
VPARPC_FUNC_LOOKUP (0x0003) for user credential verification and session
creation, VPARPC_FUNC_CREDS (0x0004) for complete user profile and metadata
retrieval, VPARPC_FUNC_LOGOUT (0x0005) for session termination and cleanup, and
VPARPC_FUNC_HEARTBEAT (0x0006) for connection keep-alive and health check.

### Server Deployment Architectures

Standalone server configuration supports starting the VPA RPC server in
standalone mode with configuration file, daemon mode, and PID file support. The
server supports multiple deployment modes including standalone TCP server (
default), SSL/TLS encrypted server, Unix domain socket server, and
multi-threaded server with connection pooling.

System service integration provides xinetd configuration for the VPA service
with UNLISTED type, specified port, stream socket_type, TCP protocol, no wait,
dedicated user, server executable, and logging configuration for success and
failure events.

## Security Implementation Details

### Authentication Flow Architecture

The authentication flow follows a structured pattern where the client sends PSK
authentication to the server and receives an auth token, then sends a version
request and receives a version response, followed by a user lookup request and
receives a session handle, and finally sends a credential request and receives
the user profile.

### Security Features Implementation

Security features include encryption with AES-256 encryption for all sensitive
data transmission, authentication with multi-factor authentication using PSK and
user credentials, authorization with role-based access control and granular
permissions, session management with secure session tokens and automatic
expiration, audit logging with complete audit trail of all security events, and
input validation with comprehensive validation and sanitization of all inputs.

## Monitoring & Observability

### Logging System Architecture

The multi-level logging system provides configurable outputs with logdebug for
debug information for development, loginfo for informational system events,
logwarn for warning conditions that need attention, logerror for error
conditions requiring immediate action, and logfatal for fatal errors causing
system shutdown.

### Performance Monitoring

Performance monitoring includes response time tracking with detailed timing of
all RPC operations, resource usage monitoring with CPU, memory, and network
usage tracking, connection monitoring with active connection counts and health
status, error rate monitoring with tracking of error rates and failure patterns,
and throughput monitoring with request/response throughput measurement.

## Quick Start & Deployment Guide

### xinetd Configuration Utility

The program called "init_xinetd_vpa" is a command line utility that performs two
specific functions. The first is to assure that the /etc/services file contains
all of the required services used by the VPA & Framework. The second is to
dynamically create the /etc/xinetd.d/vpa configuration file that configures
all seven of the xinetd dynamic services. They are: vpa, vpa-disc, vpa-start,
vpa-netstat, vpa-ip, vpa-http, vpa-https. It also restarts the xinetd service.

### structures diagnostic program

The program called "structures" is a command line utility that determines the
length of the largest VPARPC request packet, and calculates any required
filler bytes needed to pad out any of the functional request packets.

### Development Environment Setup

Development environment setup includes cloning the repository and preparing the
build environment, installing dependencies for Ubuntu/Debian systems,
configuring and building the project, and running tests with make test and ctest
with output on failure.

### Production Deployment

Production deployment involves production build with optimizations, system-wide
installation, configuring system service with systemctl enable and start, and
verifying deployment with systemctl status and connection testing.

## API Reference & Integration

### Core Class Hierarchy

The main framework classes include mwfw2 for primary framework initialization,
CVpaRpc for RPC client implementation, vparpc for RPC server implementation,
window for professional console interface, semigraphics for console graphics
utilities, and CSysLog for system logging implementation. Utility classes
include config for configuration management, environment for environment
variable handling, password for password and credential management, shared for
shared memory operations, and osIface for operating system interface.

### Essential API Methods

RPC client operations include get_auth() for getting authentication token,
get_version() for getting server version, get_lookup() for performing user
lookup, get_creds() for retrieving user credentials, get_creds_username() for
getting username, get_creds_firstname() for getting first name,
get_creds_lastname() for getting last name, and get_creds_level() for getting
authorization level. Window management operations include set_title() for
setting window title, add_row() for adding content rows, render() for rendering
the window, and clear() for clearing window content. Framework operations
include isCGI() for checking if running in CGI mode and sl_loginfo() for logging
informational messages.

## License & Legal Information

**Copyright © 2021-2025 Douglas Wade Goodall. All Rights Reserved.**

This software is proprietary and confidential. The Virtual Protocol Adapter &
Multiware Framework (mwfw2) is protected by copyright law and international
treaties. Unauthorized reproduction or distribution of this software, or any
portion of it, may result in severe civil and criminal penalties, and will be
prosecuted to the maximum extent possible under the law.

### Usage Rights

This software is licensed for use by authorized users only. All rights not
expressly granted are reserved. No part of this software may be reproduced,
distributed, or transmitted in any form. Reverse engineering, decompilation, or
disassembly is prohibited.

### Support & Contact Information

For technical support, licensing inquiries, or collaboration opportunities,
contact the development team through authorized channels. Comprehensive API
reference is available in the `/doc` directory. Submit bug reports through the
appropriate issue tracking system. Contact the product management team for
feature requests.

---

**Virtual Protocol Adapter & Multiware Framework** - *Professional distributed
computing solutions for enterprise environments*

*Version 5.5.10.2 | Built with C++20 | Optimized for modern distributed systems*

*Empowering secure, scalable, and sophisticated distributed applications since
2021*
