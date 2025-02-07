# Bulk Candy Price Checker

This C project helps you calculate candy prices using real-time market data and bulk discounts. The way it works is by retrieving the latest prices via an API, or it defaults to $1.99 per unit if unavailable. A 7% sales tax is applied. I would recommend using Zylalabs API since it has a free trial. It will automatically apply bulk discounts for larger orders, and can validate the input is correct (numeric and positive values).

## Example Output
```
Enter the number of chocolate bars: 200
Fetching real-time chocolate prices...
Price per bar: $1.75
Total price (including tax): $319.45

```

